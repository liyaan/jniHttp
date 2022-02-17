package com.ldlywt.jnihttp

import com.google.gson.Gson

class HttpRequest:HttpConnectionImpl {
    override fun addHeader(): String {
        return "token:6b780e5f-680b-411f-99a4-6604d5c16391,version:3.7.8,symbol:2," +
                "HTTP_TOKEN:6b780e5f-680b-411f-99a4-6604d5c16391"
    }

    override fun get(url: String) :String{
        return HttpConnections.httpGetFrom(url, addHeader())
    }

    override fun get(url: String, params: MutableList<HttpConnectionBean>) :String{
        val sb = StringBuilder(url)
        // 如果有实体数据上传，则拼接实体字符串
        if (params != null && !params.isEmpty()) {
            sb.append('?')
            for (pair in params) {
                sb.append(pair.name).append('=').append(pair.value).append('&')
            }
            sb.deleteCharAt(sb.length - 1)
        }
        return HttpConnections.httpGetFrom(sb.toString(), addHeader())
    }
    override fun postFromData(url: String, list: MutableList<HttpConnectionBean>):String {
        val json = Gson().toJson(list)
        return HttpConnections.httpPostFromData(url,json, addHeader())
    }
    override fun postJson(url: String, json: String) :String{
        return HttpConnections.httpPostFromJson(url,json, addHeader())
    }


}