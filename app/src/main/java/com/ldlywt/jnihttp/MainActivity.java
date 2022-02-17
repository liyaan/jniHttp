package com.ldlywt.jnihttp;

import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.google.gson.Gson;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
//        HttpConfig.INSTANCE.httpConnect(new HttpRequest());
//        HttpConfig.INSTANCE
//                .url("请求的URL")
//                .get(it ->{
//                    Log.i("LIYAAN",it);
//                    return null;
//                });
//        HttpConfig.INSTANCE
//                .postValue("Post请求的json")
//                .url("请求的URL")
//                .post(it->{
//                    Log.i("LIYAAN",it);
//                    return null;
//                });

        List<ValueName> list = new ArrayList<>();
        String json =  new Gson().toJson(list);
        HttpConnections.INSTANCE.httpPostCookieForm(
                "post from data 请求接口",
                json
                );
        HttpConnections.INSTANCE
                .httpGetCookieForm("请求接口");

    }


}
