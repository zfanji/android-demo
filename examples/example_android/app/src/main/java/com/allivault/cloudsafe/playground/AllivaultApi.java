package com.allivault.cloudsafe.playground;

import android.util.Log;

/**
 * Wrapper of ALLIVaultCoreP library.
 */
public class AllivaultApi {
    private static final String TAG = "MainActivity";
    static {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("allivault-api");
    }

    public static native String getMessage();
    public static native String getLibGit2Version();
    public static native boolean createRSAKeyPair(String uname);
    public static native boolean createUserAccountOnServer(
            String userName, String passWord, String fullName, String emailAddress,
            String publicKeyFile, long curTime, long expirationTime, long quotaSize);
    public static native void processNewUser(String userName);
    public static native void batchActionsForNewMachine();
    public static native void appInitialize(String rootPath);
    public static native boolean registerAppStatusUpdated();
    public static void appStatusUpdatedCallback()
    {
        Log.v(TAG, "Java callback method invoked.");
    }
}
