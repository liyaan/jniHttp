#include <jni.h>
#include <string>
#include "JniUtils.h"
#include "web_task.h"
#include "cJSON.h"
#include "parson.h"
using namespace std;

#define JNI_UTILS_LIST "java/util/List"

extern "C"
jstring
Java_com_ldlywt_jnihttp_HttpConnections_httpFromJNI(JNIEnv *env, jobject /* this */) {
    //GET请求
    string url = "http://www.weather.com.cn/data/sk/101280601.html";
    WebTask task;
    task.SetUrl(url.c_str());
    task.SetConnectTimeout(5);
    task.DoGetString();
    if (task.WaitTaskDone() == 0) {
        //请求服务器成功
        string jsonResult = task.GetResultString();
        LOGI("返回的json数据是：%s\n", jsonResult.c_str());
        return env->NewStringUTF(jsonResult.c_str());
    } else {
        LOGI("网络连接失败\n");
        return env->NewStringUTF("网络连接失败！");
    }
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_ldlywt_jnihttp_HttpConnections_httpPostJni(JNIEnv *env, jobject thiz, jstring url) {
    string url_ = env->GetStringUTFChars(url,0);
    WebTask task;
    task.SetUrl(url_.c_str());
    task.SetConnectTimeout(5);
    task.AddPostString("page", "1");
    task.AddPostString("page_size", "100");
    task.DoGetString();
    if (task.WaitTaskDone() == 0) {
        //请求服务器成功
        string jsonResult = task.GetResultString();
        LOGI("返回的json数据是：%s\n", jsonResult.c_str());
        return env->NewStringUTF(jsonResult.c_str());
    } else {
        LOGI("网络连接失败\n");
        return env->NewStringUTF("网络连接失败！");
    }
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_ldlywt_jnihttp_HttpConnections_httpHeaderJni(JNIEnv *env, jobject thiz,
        jstring url, jstring map) {
    string url_ = env->GetStringUTFChars(url,0);
    WebTask task;
    task.addHeader(env->GetStringUTFChars(map,0));
    task.SetUrl(url_.c_str());
    task.SetConnectTimeout(5);
    task.DoGetString();
    if (task.WaitTaskDone() == 0) {
        //请求服务器成功
        string jsonResult = task.GetResultString();
        JSON_Value *root_value = json_parse_string(jsonResult.c_str());
        JSON_Value_Type jsonValueType = json_value_get_type(root_value);
        if (jsonValueType == JSONObject){
            JSON_Object *jsonObject = json_value_get_object(root_value);
            double code = json_object_get_number(jsonObject,"code");

            int _code = code;
            if (_code==0){
                LOGI("请求成功");
            }else{
                LOGI("网络连接失败=%d\n",_code);
            }

        }
        return env->NewStringUTF(jsonResult.c_str());
    } else {
        LOGI("网络连接失败\n");
        return env->NewStringUTF("网络连接失败！");
    }
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_ldlywt_jnihttp_HttpConnections_httpHeaderJniPost(JNIEnv *env,
        jobject thiz, jstring url,jstring header,jstring json) {
    string url_ = env->GetStringUTFChars(url,0);
    WebTask task;
    task.addHeader(env->GetStringUTFChars(header,0));
    task.postJsonRequest(env->GetStringUTFChars(json,0));
    task.SetUrl(url_.c_str());
    task.SetConnectTimeout(5);
    LOGI("json参数数据：%s\n",env->GetStringUTFChars(json,0));
    task.DoGetString();
    if (task.WaitTaskDone() == 0) {
        //请求服务器成功
        string jsonResult = task.GetResultString();
        LOGI("返回的json数据是：%s\n", jsonResult.c_str());
        return env->NewStringUTF(jsonResult.c_str());
    } else {
        LOGI("网络连接失败:%d\n",task.WaitTaskDone());
        return env->NewStringUTF("网络连接失败！");
    }

}
jstring backJson(JNIEnv *env,string jsonResult){
    //请求服务器成功
    JSON_Value *root_value = json_parse_string(jsonResult.c_str());
    JSON_Value_Type jsonValueType = json_value_get_type(root_value);
    LOGI("返回的json数据是：%s\n", jsonResult.c_str());
    if (jsonValueType == JSONObject){
        JSON_Object *jsonObject = json_value_get_object(root_value);
        double code = json_object_get_number(jsonObject,"code");
        int _code = code;
        if (_code==0){
            LOGI("请求成功");
        }else{
            LOGI("网络连接失败=%d\n",_code);
        }

    }
    return env->NewStringUTF(jsonResult.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_ldlywt_jnihttp_HttpConnections_httpGetFrom(JNIEnv *env,
        jobject thiz, jstring url,
        jstring header) {
    string url_ = env->GetStringUTFChars(url,0);
    string header_ = env->GetStringUTFChars(header,0);
    WebTask task;
    task.addHeader(header_.c_str());
    task.SetUrl(url_.c_str());
    task.SetConnectTimeout(30);
    task.DoGetString();
    if (task.WaitTaskDone() == 0) {
        //请求服务器成功
        string jsonResult = task.GetResultString();
        LOGI("网络连接成功:%s\n",jsonResult.c_str());
        //      return env->NewStringUTF("网络连接成功！");
        return backJson(env,jsonResult.c_str());
    } else {
        LOGI("网络连接失败:%d\n",task.WaitTaskDone());
        return env->NewStringUTF("网络连接失败！");
    }
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_ldlywt_jnihttp_HttpConnections_httpPostFromJson(JNIEnv *env, jobject thiz, jstring url,
                                                     jstring json, jstring header) {
    string url_ = env->GetStringUTFChars(url,0);
    WebTask task;
    task.addHeader(env->GetStringUTFChars(header,0));
    task.postJsonRequest(env->GetStringUTFChars(json,0));
    task.SetUrl(url_.c_str());
    task.SetConnectTimeout(30);
    task.DoGetString();
    LOGI("json参数数据：%s\n",env->GetStringUTFChars(json,0));
    if (task.WaitTaskDone() == 0) {
        //请求服务器成功
        string jsonResult = task.GetResultString();
        LOGI("网络连接成功:%s\n",jsonResult.c_str());
        //       return env->NewStringUTF("网络连接成功！");
        return backJson(env,jsonResult.c_str());
    } else {
        LOGI("网络连接失败:%d\n",task.WaitTaskDone());
        return env->NewStringUTF("网络连接失败！");
    }
}
extern "C"
void addPostDataList(JNIEnv *env,WebTask task,jobject obj){
    jclass list_cls =env->FindClass(JNI_UTILS_LIST);
    jmethodID listInit = env->GetMethodID(list_cls,"<init>", "()V");
    jmethodID listGet = env->GetMethodID(list_cls,"get", "(I)Ljava/lang/Object;");
    jmethodID listSet = env->GetMethodID(list_cls,"set",
            "(ILjava/lang/Object;)Ljava/lang/Object;");
    jmethodID listSize = env->GetMethodID(list_cls,"size", "()I");
    jobject list = env->NewObject(list_cls,listInit);
    int size = env->CallIntMethod(obj,listSize);
    int index = 0;
    for (index = 0;  index<size ; index++) {
       jstring str = static_cast<jstring>(env->CallObjectMethod(obj, listGet, index));

    }
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ldlywt_jnihttp_HttpConnections_httpPostFromData(JNIEnv *env, jobject thiz, jstring url,
                                                         jstring json, jstring header) {
    string url_ = env->GetStringUTFChars(url,0);
    string header_ = env->GetStringUTFChars(header,0);
    WebTask task;
    task.addHeaderFrom(header_);
    const char* json_ = env->GetStringUTFChars(json,0);
    JSON_Value *root_value = json_parse_string(json_);
    JSON_Value_Type jsonValueType = json_value_get_type(root_value);
    if (jsonValueType == JSONObject){
        JSON_Object *commit = json_value_get_object(root_value);
        string json_name = json_object_get_string(commit,"name");
        string json_value = json_object_get_string(commit,"value");
        task.AddPostString(json_name.c_str(),json_value.c_str());
    }else if (jsonValueType == JSONArray){
        JSON_Array *commits  = json_value_get_array(root_value);
        for (int i = 0; i < json_array_get_count(commits); i++) {
            JSON_Object *commit = json_array_get_object(commits,i);
            string json_name = json_object_get_string(commit,"name");
            string json_value = json_object_get_string(commit,"value");
            task.AddPostString(json_name.c_str(),json_value.c_str());
        }
    }
    env->ReleaseStringUTFChars(header,json_);
    task.SetUrl(url_.c_str());
    task.SetConnectTimeout(30);
    if (task.WaitTaskDone() == 0) {
        //请求服务器成功
        string jsonResult = task.GetResultString();
        return backJson(env,jsonResult);
    } else {
        LOGI("网络连接失败:%d\n",task.WaitTaskDone());
        return env->NewStringUTF("网络连接失败！");
    }

}