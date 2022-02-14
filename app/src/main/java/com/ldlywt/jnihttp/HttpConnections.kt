package com.ldlywt.jnihttp

object HttpConnections {
    init {
        System.loadLibrary("native-lib");
    }
    external fun httpFromJNI(): String?
    external fun httpPostJni(url: String?): String?
    external fun httpHeaderJni(url: String?, header: String?): String?
    external fun httpHeaderJniPost(url: String?, header: String?, json: String?): String?


    external fun httpGetFrom(url:String,header: String):String
    external fun httpPostFromJson(url:String,json:String,header: String):String
    external fun httpPostFromData(url:String,json:String,header: String):String
}