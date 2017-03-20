package com.clam314.hellojni;

import android.util.Log;

import java.util.Locale;

/**
 * Created by clam314 on 2017/3/20
 */

public class ParameterTest {
    private static final String TAG = ParameterTest.class.getSimpleName();
    private static int num = 0;
    private String str;

    public ParameterTest(){
    }

    public ParameterTest(String str,int num){
        this.str = str;
        ParameterTest.num = num;
    }

    public static void callStaticMethod(String str,int i){
        Log.d(TAG,String.format("ClassMethod::callStaticMethod called!-->str=%s," + " i=%d\n", str, i));
    }

    public void callInstanceMethod(String str,int i){
        Log.d(TAG,String.format("ClassMethod::callInstanceMethod called!-->str=%s," + " i=%d\n", str, i));
    }

    public String getStr() {
        return str;
    }

    public void setStr(String str) {
        this.str = str;
    }

    public static int getNum() {
        return num;
    }

    public static void setNum(int num) {
        ParameterTest.num = num;
    }

    @Override
    public String toString() {
        String s = String.format(Locale.CHINA,"ParameterTest num=%d str=%s",num,str);
        Log.d(TAG,s);
        return s;
    }
}
