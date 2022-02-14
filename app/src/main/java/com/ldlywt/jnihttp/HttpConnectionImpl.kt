package com.ldlywt.jnihttp

interface HttpConnectionImpl {
    fun addHeader():String
    fun get(url:String):String
    fun get(url:String,list:MutableList<HttpConnectionBean>):String

    fun postFromData(url:String,list:MutableList<HttpConnectionBean>):String
    fun postJson(url:String,json:String):String
}