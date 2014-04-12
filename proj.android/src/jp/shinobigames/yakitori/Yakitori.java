/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package jp.shinobigames.yakitori;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;
import android.util.Log;

public class Yakitori extends Cocos2dxActivity{
	
	private static final String TAG = "Yakitori";
	private static Yakitori mMyActivity;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		mMyActivity = this;
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// Yakitori should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }
    
	public static String getLocalizeString(String key) {
		if ("app_name".equals(key)) {
			return mMyActivity.getString(R.string.app_name);
		} else if ("Sale".equals(key)) {
			return mMyActivity.getString(R.string.Sale);
		} else if ("SaleFormat".equals(key)) {
			return mMyActivity.getString(R.string.SaleFormat);
		} else if ("SaleSuffix".equals(key)) {
			return mMyActivity.getString(R.string.SaleSuffix);
		} else if ("BestSale".equals(key)) {
			return mMyActivity.getString(R.string.BestSale);
		} else if ("AccumulationSales".equals(key)) {
			return mMyActivity.getString(R.string.AccumulationSales);
		} else if ("Tweet".equals(key)) {
			return mMyActivity.getString(R.string.Tweet);
		} else if ("FaceBookSend".equals(key)) {
			return mMyActivity.getString(R.string.FaceBookSend);
		} else if ("AppUrl".equals(key)) {
			return mMyActivity.getString(R.string.AppUrl);
		} else if ("AppStoreListUrl".equals(key)) {
			return mMyActivity.getString(R.string.AppStoreListUrl);
		} else if ("OverAlert".equals(key)) {
			return mMyActivity.getString(R.string.OverAlert);
		} else if ("RareAlert".equals(key)) {
			return mMyActivity.getString(R.string.RareAlert);
		} else if ("ThanksMessage".equals(key)) {
			return mMyActivity.getString(R.string.ThanksMessage);
		} else if ("ScorchedMessage".equals(key)) {
			return mMyActivity.getString(R.string.ScorchedMessage);
		}
		return "";
	}
	
	public static String getLanguage() {
        return mMyActivity.getResources().getConfiguration().locale.getLanguage();
    }
}
