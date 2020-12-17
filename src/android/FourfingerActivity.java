package com.outsystemsenterprise.entel.PEMiEntel.cordova.plugin;

// Cordova-required packages
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.PluginResult;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.annotation.TargetApi;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AlertDialog;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;

import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.veridiumid.sdk.activities.DefaultVeridiumSDKModelFactory;
import com.veridiumid.sdk.defaultdata.VeridiumSDKDataInitializer;
import com.veridiumid.sdk.fourf.VeridiumSDKFourFInitializer;
import com.veridiumid.sdk.model.exception.SDKInitializationException;

import com.veridiumid.sdk.IVeridiumSDK;
import com.veridiumid.sdk.VeridiumSDK;
import com.veridiumid.sdk.analytics.Analytics;
import com.veridiumid.sdk.fourf.ExportConfig;
import com.veridiumid.sdk.fourf.FourFInterface;
import com.veridiumid.sdk.fourf.FourFIntegrationWrapper;
import com.veridiumid.sdk.model.biometrics.packaging.IBiometricFormats;
import com.veridiumid.sdk.model.biometrics.results.BiometricResultsParser;
import com.veridiumid.sdk.model.biometrics.results.handling.IBiometricResultsHandler;
import com.veridiumid.sdk.licensing.exception.LicenseException;
import com.veridiumid.sdk.support.base.VeridiumBaseActivity;
import com.veridiumid.sdk.support.help.ToastHelper;

import android.content.res.Resources;

import android.widget.Button;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;


public class FourfingerActivity extends Activity  {

    private IVeridiumSDK mBiometricSDK;

    // operation strings
    private static final int REQUEST_APP_PREF = 168;
    private static final int REQUEST_EXPORT = 314;
    private static final int REQUEST_ENROL = 324;
    private static final int REQUEST_AUTH = 334;

    private String package_name;
	private Resources resources;

    private AlertDialog dialog_permissions;

    private static final String[] requiredPermissions = new String[]{
            Manifest.permission.CAMERA,
            Manifest.permission.INTERNET
    };

    private static int RIGHT_THUMB = 1;
    private static int RIGHT_INDEX = 2;
    private static int RIGHT_MIDDLE = 3;
    private static int RIGHT_RING = 4;
    private static int RIGHT_PINKY = 5;

    private static int LEFT_THUMB = 6;
    private static int LEFT_INDEX = 7;
    private static int LEFT_MIDDLE = 8;
    private static int LEFT_RING = 9;
    private static int LEFT_PINKY = 10;

    private int BestFingerRight;
    private int BestFingerLeft;


    private String TAG = "FourfingerActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        setContentView(getResourceId("layout/activity_fourfinger"));

        Log.d(TAG,"On create");

        BestFingerRight = getIntent().getIntExtra("RightFinger",2);
        BestFingerLeft = getIntent().getIntExtra("LeftFinger",7);

        Log.d(TAG,"intent got. Left " + String.valueOf(BestFingerLeft) + "Right " + String.valueOf(BestFingerRight) );

        preInitSDK();

        if(initSDK()){

            configureExportSettings();

        }   

        Analytics.init(this);

        if (Build.VERSION.SDK_INT > 22) {

            Log.d(TAG,"Requesting Permissions");
            checkPermissions(requiredPermissions);
        }else{
            
            abrir4Finger();
        }

    }

    @TargetApi(Build.VERSION_CODES.M)
    public void checkPermissions(@NonNull String... permissions) {

        List<String> ungranted = new ArrayList<String>();
        for (String permission : permissions) {
            if (ContextCompat.checkSelfPermission(this,
                    permission)
                    != PackageManager.PERMISSION_GRANTED) {
                ungranted.add(permission);
            }
        }

        if (ungranted.size() != 0) {
            ActivityCompat.requestPermissions(this,
                    ungranted.toArray(new String[0]),
                    REQUEST_APP_PREF);
        }else{
            Log.d(TAG,"hasPermissions");
            abrir4Finger();
        }
    }
    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String permissions[], int[] grantResults) {

        Log.d(TAG,"onRequestPermissionsResult");
        Boolean hasAllPermissions = true;                                               
        for (int r : grantResults) {
            if (r != PackageManager.PERMISSION_GRANTED) {
                hasAllPermissions = false;
                showDeniedPermissionsDialog();
                break;
            }
        }

        if(hasAllPermissions){

            Log.d(TAG,"hasAllPermissions");
            abrir4Finger();
        }

    }
    private void showDeniedPermissionsDialog() {

        Log.d(TAG,"showDeniedPermissionsDialog");
        if (dialog_permissions != null) {
            if (dialog_permissions.isShowing()) {
                return;
            }
        }

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("Esta aplicación requiere los permisos solicitados. Por favor, acéptelos a en la configuración de Android.")
                .setCancelable(false)
                .setPositiveButton("OK", (dialog, id) -> finish());
        dialog_permissions = builder.create();
        dialog_permissions.show();
    }

    private void abrir4Finger(){

        Log.d(TAG,"Abrir 4Finger!");

        if (mBiometricSDK != null) {
                
            Intent exportIntent = mBiometricSDK.export(FourFInterface.UID);
            startActivityForResult(exportIntent, REQUEST_EXPORT);

        }else{
            ToastHelper.showMessage(FourfingerActivity.this, "Licence is invalid!");
            Log.e(TAG, "IVeridiumSDK object not initialised");
        }

    }

    private int getResourceId (String typeAndName)
    {
        if(package_name == null) package_name = getApplication().getPackageName();
        if(resources == null) resources = getApplication().getResources();
        return resources.getIdentifier(typeAndName, null, package_name);
    }

    
    /*
     * Initialise the SDK and ensure the licence is valid.
     */
    private boolean initSDK() {

        try {
            mBiometricSDK = VeridiumSDK.getSingleton();
            return true;
        } catch (LicenseException e) {
            ToastHelper.showMessage(FourfingerActivity.this, "Licence is invalid!");
            e.printStackTrace();
        }
        return false;
    }

    /*
     * Configure Export settings using ExportConfig
     * Capture either hand, JSON container format, PNG with multiple scales, liveness on
     */
    private void configureExportSettings(){

        ExportConfig.setFormat(IBiometricFormats.TemplateFormat.FORMAT_JSON);

        if(BestFingerRight == RIGHT_THUMB){
            ExportConfig.setFingersToCapture(Arrays.asList(ExportConfig.FingerID.THUMB_RIGHT ));
        }else if(BestFingerLeft == LEFT_THUMB){
            ExportConfig.setFingersToCapture(Arrays.asList(ExportConfig.FingerID.THUMB_LEFT ));
        }else{
            ExportConfig.setFingersToCapture(ExportConfig.ExportMode.FOUR_F_RIGHT_SWITCHABLE);
        }
        

        ExportConfig.setPack_bmp(false);
        ExportConfig.setPack_png(false);
        ExportConfig.setPack_raw(false);
        ExportConfig.setPack_wsq(true);
        ExportConfig.setPackExtraScale(true);
      	
      	ExportConfig.setFixedPrintSize(512, 512);

        ExportConfig.setUseLiveness(true);

        //add Conf

        ExportConfig.setCalculate_NFIQ(true);
        ExportConfig.setUseNistType4(false);
        ExportConfig.setPackDebugInfo(true); //
        ExportConfig.setPackAuditImage(true); //
        /*

        ExportConfig.setWSQCompressRatio(ExportConfig.WSQCompressRatio.COMPRESS_10to1);

        //ExportConfig.setFixedPrintSize(0,0);
        */
    }


    /* A custom IBiometricResultsHandler, handles the resulting data from an operation
     */
    IBiometricResultsHandler resultHandler = new IBiometricResultsHandler() {
        @Override
        public void handleSuccess(Map<String, byte[][]> results) {
            ToastHelper.showMessage(FourfingerActivity.this, "Escaneo Exitoso");
            // Handle exported templates here

            byte[] template = null;
            for (Map.Entry<String, byte[][]> entry : results.entrySet()) {
                String bio_key = entry.getKey();
                byte[][] data = entry.getValue();

                String templateString;

                if(bio_key.equals(FourFInterface.UID)){
                    // template data is contained with the first element
                    template = data[1];

                    ConvertByteArray(template);

                }
            }
        }

        @Override
        public void handleFailure() {
            ToastHelper.showMessage(FourfingerActivity.this, "Escaneo Fallido");
            Intent i = new Intent();
            i.putExtra("status", "Escaneo Fallido");
            setResult(Activity.RESULT_CANCELED, i);
            finish();
        }

        @Override
        public void handleCancellation() {
            ToastHelper.showMessage(FourfingerActivity.this, "Escaneo Cancelado");

            Intent i = new Intent();
            i.putExtra("status", "Escaneo Cancelado");
            setResult(Activity.RESULT_CANCELED, i);
            finish();
        }

        @Override
        public void handleError(String message) {
            ToastHelper.showMessage(FourfingerActivity.this, "Error: " + message, Toast.LENGTH_LONG);

            Intent i = new Intent();
            i.putExtra("status", "Escaneo Erroneo");
            setResult(Activity.RESULT_CANCELED, i);
            finish();
        }
    };


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        Log.d(TAG,"onActivityResult");

        if (requestCode == REQUEST_APP_PREF) {
            // do nothing
        }
        else if (requestCode == REQUEST_EXPORT ||
                 requestCode == REQUEST_ENROL ||
                 requestCode == REQUEST_AUTH ) {
            BiometricResultsParser.parse(resultCode, data, resultHandler);

        }
        else {
            Toast.makeText(this, "Error: unknown request result", Toast.LENGTH_LONG).show();
        }

        super.onActivityResult(requestCode, resultCode, data);
    }


    private void ConvertByteArray(byte[] byteResponse){

        try {
            JSONObject object = new JSONObject(new String(byteResponse));
            JSONObject Scale085 = object.getJSONObject("SCALE085");
            JSONArray fingerprints = Scale085.getJSONArray("Fingerprints");

            int bestFingerI= 0;
            for(int i=0; i<fingerprints.length(); i++){
                JSONObject currentFingerprint = fingerprints.getJSONObject(i);
                int fingerPositionCode = currentFingerprint.getInt("FingerPositionCode");
                if(fingerPositionCode == BestFingerLeft || fingerPositionCode == BestFingerRight){
                    bestFingerI = i;
                    break;
                }
            }

            JSONObject currentFingerprint = fingerprints.getJSONObject(bestFingerI);
            int fingerPositionCode = currentFingerprint.getInt("FingerPositionCode");
            JSONObject fingerImpressionImage = currentFingerprint.getJSONObject("FingerImpressionImage");

            String Hand = "";
            if(fingerPositionCode == LEFT_INDEX || fingerPositionCode == LEFT_MIDDLE ||
                    fingerPositionCode == LEFT_RING || fingerPositionCode == LEFT_PINKY ||
                    fingerPositionCode == LEFT_THUMB){
                Hand = "LEFT";
            }else if(fingerPositionCode == RIGHT_INDEX || fingerPositionCode == RIGHT_MIDDLE ||
                    fingerPositionCode == RIGHT_RING || fingerPositionCode == RIGHT_PINKY ||
                    fingerPositionCode == RIGHT_THUMB){
                Hand = "RIGHT";
            }


            String respuestaWSQ = fingerImpressionImage.getString("BinaryBase64ObjectWSQ");

            Intent i = new Intent();
            i.putExtra("base64String", respuestaWSQ);
            i.putExtra("hand", Hand);
            setResult(Activity.RESULT_OK, i);
            finish();

        }catch (Exception e) {
            e.printStackTrace();
        }

    }



    private void preInitSDK() {

        Context appContext = getApplicationContext();

        try {
            // TODO add here the 4 FingersID Licence
            String fourfLicence = "kZMvQP26P5AarUh3ZO0al+FySMfBqfLnsaEP5ZRG83oqx9MKYEOSmQKoH9/fEu66Kqwfh7TAfQiViu/8rOVHA3siZGV2aWNlRmluZ2VycHJpbnQiOiJFYTNkY2MrVkVsakJhL1JWb3E0NWI1U2x4ejdndC9FTHlvVXBvSjBPOWk0PSIsImxpY2Vuc2UiOiJZd2YvZDNkcmVPeEN0Q285VDdJczZPaUZpayt0TTNOcW93VHVLRjBWNDhBL3ljUXZVTW1ZdG02TVpFNWd0Zk1wMThNNmJ3Q2xFL29BdC9aZ0RTdEVEbnNpZEhsd1pTSTZJa0pKVDB4SlFsTWlMQ0p1WVcxbElqb2lORVlpTENKc1lYTjBUVzlrYVdacFpXUWlPakUyTURnd05UY3hNell6TnpRc0ltTnZiWEJoYm5sT1lXMWxJam9pUlc1MFpXd2dkbWxoSUVsdWMyOXNkWFJwYjI1eklpd2lZMjl1ZEdGamRFbHVabThpT2lKRmJuUmxiQ0JCZFhSdlUyRnNaU0JRY205cVpXTjBJQzBnTkVaRklDMGdkalFtTlNCamIyMHVaVzUwWld3dWJXOTJhV3dzSUdOdmJTNWxiblJsYkM1dGIzWnBiQzVoZFhSdllXTjBhWFpoWTJsdmJpSXNJbU52Ym5SaFkzUkZiV0ZwYkNJNkltMXBaM1ZsYkM1b1pYSnVZVzVrWlhwQWFXNXpiMngxZEdsdmJuTXVjR1VpTENKemRXSk1hV05sYm5OcGJtZFFkV0pzYVdOTFpYa2lPaUo2TXpkRmMzaDNSRUoxWVUwNWNYQlJRMmxLU0UxUGVtOVplRkVyTml0VE5VVlFUV2d2WmxJdmFqVm5QU0lzSW5OMFlYSjBSR0YwWlNJNk1UVTRNemN5TmpRd01EQXdNQ3dpWlhod2FYSmhkR2x2YmtSaGRHVWlPakUyTWpBNU5qUTRNREF3TURBc0ltZHlZV05sUlc1a1JHRjBaU0k2TVRZeU1URXpOell3TURBd01Dd2lkWE5wYm1kVFFVMU1WRzlyWlc0aU9tWmhiSE5sTENKMWMybHVaMFp5WldWU1FVUkpWVk1pT21aaGJITmxMQ0oxYzJsdVowRmpkR2wyWlVScGNtVmpkRzl5ZVNJNlptRnNjMlVzSW1KcGIyeHBZa1poWTJWRmVIQnZjblJGYm1GaWJHVmtJanBtWVd4elpTd2ljblZ1ZEdsdFpVVnVkbWx5YjI1dFpXNTBJanA3SW5ObGNuWmxjaUk2Wm1Gc2MyVXNJbVJsZG1salpWUnBaV1FpT21aaGJITmxmU3dpWm1WaGRIVnlaWE1pT25zaVltRnpaU0k2ZEhKMVpTd2ljM1JsY21WdlRHbDJaVzVsYzNNaU9uUnlkV1VzSW1WNGNHOXlkQ0k2ZEhKMVpYMHNJbVZ1Wm05eVkyVmtVSEpsWm1WeVpXNWpaWE1pT25zaWJXRnVaR0YwYjNKNVRHbDJaVzVsYzNNaU9tWmhiSE5sZlN3aWRtVnljMmx2YmlJNklpb3VLaUo5In0=";
            VeridiumSDK.init(appContext,
                    new DefaultVeridiumSDKModelFactory(appContext),
                    new VeridiumSDKFourFInitializer(fourfLicence),
                    new VeridiumSDKDataInitializer()
            );
        } catch (SDKInitializationException e) {
            e.printStackTrace();
        }

    }

    
    private static boolean tienePermisos(Context context, String... permisos) {
        if (context != null && permisos != null) {
            for (String permiso : permisos) {
                if (ActivityCompat.checkSelfPermission(context, permiso) != PackageManager.PERMISSION_GRANTED) {
                    return false;
                }
            }
        }
        return true;
    }

} 
