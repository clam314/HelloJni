package com.clam314.hellojni;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.List;

public class HelloJniActivity extends AppCompatActivity {

    static {
        System.loadLibrary("hello-jni");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hello_jni);
        parameterInput((short) 2,1024,3333333L,0.56f,0.4444444444,'a');
        parameterStringInput("hello-jni");
        parameterArrayInput(new int[]{1,2,3,4,5,6});
        ParameterTest test = new ParameterTest();
        test.setStr("HELLO-JNI");
        ParameterTest.setNum(888);
        parameterObjectInput(test);
        callStaticMethod();
        callInstanceMethod(test);
        ParameterTest test1 = getInstance("etParameterTestInstance",999);
        test1.toString();
        List<ParameterTest> list = getParameterTestList(3);
        for (ParameterTest t: list){
            t.toString();
        }
    }

    //传入基本类型
    private native void parameterInput(short s,int i,long l, float f, double d, char c);
    //传入字符串
    private native void parameterStringInput(String s);
    //传入数组
    private native void parameterArrayInput(int[] array);
    //传入对象
    private native void parameterObjectInput(ParameterTest parameter);
    //在本地方法里面调用Java类的静态方法
    private native void callStaticMethod();
    //在本地方法里面调用Java对象的方法
    private native void callInstanceMethod(ParameterTest parameter);
    //返回一个对象
    private native ParameterTest getInstance(String str,int num);
    //返回一个list
    private native ArrayList<ParameterTest> getParameterTestList(int size);
}
