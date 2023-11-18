package com.example.stt;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.speech.tts.TextToSpeech;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Locale;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private final int REQ_CODE = 100;
    TextToSpeech mTTS; //文字轉語音
    TextView textView; //語音轉文字得到的內容
    EditText editText; //鍵盤輸入的內容

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("SpeechToText and TextToSpeech");//標題

        textView = findViewById(R.id.text5); //將textView選至text5(語音抓到的文字)
        editText = findViewById(R.id.editText); //將editText選至editText(使用者輸入的文字)
        Button button=findViewById(R.id.button); //將button選至button(檢查文字)
        Button button2=findViewById(R.id.button2); //將button2選至button2(點擊說話)
        Button button3=findViewById(R.id.button3); //將button3選至button3(播放文字)

        button2.setOnClickListener(new View.OnClickListener() { //當使用者按下button2時
            @Override
            public void onClick(View v) {
                String string1 = editText.getText().toString(); //將editText的內容轉為string並存入string1
                editText.setEnabled(false); //當使用者按下button2後便不能修改editText的內容(防止作弊)

                //以下為SpeechToString
                Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
                intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
                intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
                intent.putExtra(RecognizerIntent.EXTRA_PROMPT, string1);
                try {
                    startActivityForResult(intent, REQ_CODE);
                }catch (ActivityNotFoundException a){
                    Toast.makeText(getApplicationContext(), "您的裝置不支援此操作", Toast.LENGTH_SHORT).show();
                }
            }
        });

        //以下為StringToSpeech
        mTTS = new TextToSpeech(this, new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                if (status == TextToSpeech.SUCCESS) {
                    int result = mTTS.setLanguage(Locale.CHINA);
                    if (result == TextToSpeech.LANG_MISSING_DATA || result == TextToSpeech.LANG_NOT_SUPPORTED) {
                        Log.e("TTS", "Language not supported");
                    }
                    else {
                        button3.setEnabled(true);
                    }
                }
                else {
                    Log.e("TTS", "Initialization failed");
                }
            }
        });

        button3.setOnClickListener(new View.OnClickListener() { //當使用者按下button3時
            @Override
            public void onClick(View v) {
                speak(); //呼叫speak函式
            }
        });
        button.setOnClickListener(this); //當使用者按下button時
    }

    private void speak() {
        String text = editText.getText().toString(); //將editText的內容轉為string並存入text
        mTTS.speak(text, TextToSpeech.QUEUE_FLUSH, null); //呼叫mTTS函式
    }

    //以下為SpeechToString
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case REQ_CODE: {
                if (resultCode == RESULT_OK && null != data) {
                    ArrayList result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                    textView.setText(result.get(0).toString());
                }
                break;
            }
        }
    }

    @Override
    public void onClick(View v) { //當使用者按下button時
        editText.setEnabled(true); //使使用者可以修改editText
        String string1 = editText.getText().toString(); //將editText的內容轉為string並存入string1
        String string2 = textView.getText().toString(); //將textView的內容轉為string並存入string2
        String answer = null; //要跳出的訊息
        Boolean a; //存string1和string2的比較結果
        a = string1.equals(string2); //比較string1和string2
        if (a==true){ //當string1和string2相等
            answer="正確"; //修改answer為"正確"
        }
        else if (a==false){ //當string1和string2不相等
            answer="錯誤"; //修改answer為"錯誤"
        }
        Toast.makeText(this, answer, Toast.LENGTH_SHORT).show(); //顯示訊息
    }

}