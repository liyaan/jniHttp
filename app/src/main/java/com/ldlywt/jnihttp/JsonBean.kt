package com.ldlywt.jnihttp

class JsonBean<T>:HttpCodeImpl {
    private var code = 0
    private var message: String? = null
    private var data: T? = null
}