package com.ldlywt.jnihttp

import android.util.Log

object HttpConfig {
    private var httpConnection:HttpConnectionImpl? = null
    private var mUrl:String? = null
    private var mHeader:String? = null
    private var mJson:String? = null
    private var mList: MutableList<HttpConnectionBean>? = null
    fun httpConnect(httpConnect:HttpConnectionImpl){
        this.httpConnection = httpConnect
    }

    fun url(url:String):HttpConfig{
        this.mUrl = url
        return this
    }

    fun get(method: (String) -> Unit){
        mUrl?.let {
            method(httpConnection?.get(it)?:"")
        }?:let {
            Log.i("httpConnection","url not null")
        }
    }
    fun postValue(json:String):HttpConfig{
        this.mJson = json
        return this
    }
    fun postValue(list: MutableList<HttpConnectionBean>):HttpConfig{
        this.mList = list
        return this
    }
    fun post(method: (String) -> Unit){
        mUrl?.let { url->
            mJson?.let {
                method(httpConnection?.postJson(url, it)?:"")
            }
            mList?.let {
                if (it.size>0)
                    method(httpConnection?.postFromData(url, it)?:"")
                else
                    Log.i("httpConnection","url list not null")
            }
        }?:let {
            Log.i("httpConnection","url not null")
        }

    }

}