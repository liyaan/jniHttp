package com.ldlywt.jnihttp
/**
 * jni 方法定义
 * */
object HttpConnections {
    init {
        System.loadLibrary("native-lib");
    }
    external fun httpFromJNI(): String?
    external fun httpPostJni(url: String?): String?
    external fun httpHeaderJni(url: String?, header: String?): String?
    external fun httpHeaderJniPost(url: String?, header: String?, json: String?): String?

    //GET请求
    external fun httpGetFrom(url:String,header: String):String
    //post 请求 传json
    external fun httpPostFromJson(url:String,json:String,header: String):String
    //post 请求 传from表单
    external fun httpPostFromData(url:String,json:String,header: String):String
}