package com.proj.narsen;

import android.content.Context;
import android.os.Bundle;
import android.view.WindowManager;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

public class NarutoSenki extends Cocos2dxActivity {

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON
        );
    }

    public Cocos2dxGLSurfaceView onCreateGLSurfaceView() {
        return new LuaGLSurfaceView(this);
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }
}

class LuaGLSurfaceView extends Cocos2dxGLSurfaceView {

    public LuaGLSurfaceView(Context context) {
        super(context);
    }

    // NOTE: there used to be an onKeyDown() override here that force-killed
    // the process on KEYCODE_BACK (android.os.Process.killProcess(...)).
    // That intercepted the back button before it could ever reach
    // Cocos2dxGLSurfaceView's own onKeyDown(), which is what normally
    // queues KEYCODE_BACK into mCocos2dxRenderer.handleKeyDown() and, from
    // there, into the native/C++ side's Layer::keyBackClicked() dispatch
    // (see StartMenu::keyBackClicked, SelectLayer::keyBackClicked,
    // CreditsLayer::keyBackClicked, etc). With the override removed, back
    // falls through to the base class's correct handling, so those C++
    // overrides -- and the Exit button, which calls keyBackClicked()
    // itself in StartMenu::onExitCallBack() -- start actually working on
    // Android instead of hard-killing the app or doing nothing.
}