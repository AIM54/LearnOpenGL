package com.bian.learnopengl.util;

import android.util.Log;


public class LogUtils {
    public static final String TAG = "BIAN";
    public static final String SEPARATOR = " , ";
    static boolean shallLog = true;

    public static void logMessageI(String msg) {
        if (!shallLog) {
            return;
        }
        StackTraceElement stackTraceElement = Thread.currentThread().getStackTrace()[3];
        Log.i(TAG, getLogInfo(stackTraceElement) + TAG + " --- " + msg);
    }

    /**
     * 输出日志所包含的信息
     */
    public static String getLogInfo(StackTraceElement stackTraceElement) {
        StringBuilder logInfoStringBuilder = new StringBuilder();
        // 获取线程名
        String threadName = Thread.currentThread().getName();
        // 获取线程ID
        long threadID = Thread.currentThread().getId();
        // 获取文件名.即xxx.java
        String fileName = stackTraceElement.getFileName();
        // 获取类名.即包名+类名
        String className = stackTraceElement.getClassName();
        // 获取方法名称
        String methodName = stackTraceElement.getMethodName();
        // 获取生日输出行数
        int lineNumber = stackTraceElement.getLineNumber();

        logInfoStringBuilder.append("[ ");
        logInfoStringBuilder.append(threadName).append(SEPARATOR);
        logInfoStringBuilder.append(fileName).append(SEPARATOR);
        logInfoStringBuilder.append("lineNumber=" + lineNumber);
        logInfoStringBuilder.append(" ]  ");
        logInfoStringBuilder.append(methodName + ":  ");
        return logInfoStringBuilder.toString();
    }

}
