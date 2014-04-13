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

import java.util.Locale;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import net.app_c.cloud.sdk.AppCCloud;

import com.google.android.gms.ads.*;

public class Yakitori extends Cocos2dxActivity{
	
	private static final String TAG = "Yakitori";
	private static Yakitori mMyActivity;
	private WebView m_webView;
	private LinearLayout m_webLayout;
	
	private AppCCloud appCCloud;
	private AdView adView;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		mMyActivity = this;
		//web layout 
		m_webLayout = new LinearLayout(this);
		mMyActivity.addContentView(m_webLayout, 
				new LayoutParams(LayoutParams.FILL_PARENT,LayoutParams.FILL_PARENT));
		// appC cloud push on
        appCCloud = new AppCCloud(this).on(AppCCloud.API.PUSH).start();
        
        // AdMob
        // adView を作成する
        adView = new AdView(this);
        adView.setAdUnitId("ca-app-pub-6202650789898961/5851718842");
        adView.setAdSize(AdSize.BANNER);
        
        FrameLayout.LayoutParams adParams = new FrameLayout.LayoutParams(
        		LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        adParams.gravity = (Gravity.BOTTOM|Gravity.CENTER); 
        addContentView(adView, adParams);

        // 一般的なリクエストを行う
        AdRequest adRequest = new AdRequest.Builder().build();

        // 広告リクエストを行って adView を読み込む
        adView.loadAd(adRequest);
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
		Locale local = mMyActivity.getResources().getConfiguration().locale;
        if (Locale.JAPAN.equals(local) || Locale.CHINA.equals(local)) {
        	return local.getLanguage();
        }
        return "en";
    }
	
	public static void tweet(int score){
        Intent intent = new Intent();
        intent.setAction(Intent.ACTION_SEND);
        intent.setType("text/plain");
        String msg = String.format(mMyActivity.getString(R.string.Tweet), score);
        intent.putExtra(Intent.EXTRA_TEXT, msg);
        mMyActivity.startActivity(intent);
    }
	
	public static void sendFacebook(int score){
        Intent intent = new Intent();
        intent.setAction(Intent.ACTION_SEND);
        intent.setType("text/plain");
        String msg = String.format(mMyActivity.getString(R.string.FaceBookSend), score);
        intent.putExtra(Intent.EXTRA_TEXT, msg);
        mMyActivity.startActivity(intent);
    }
	
	public static void showAppPage() {
		Uri uri = Uri.parse("market://details?id=com.iankohbo.gnavi");
		Intent intent = new Intent(Intent.ACTION_VIEW, uri);
		mMyActivity.startActivity(intent);
	}
	
	public static void showAppList() {
		Uri uri = Uri.parse("https://play.google.com/store/apps/developer?id=yokochi");
		Intent intent = new Intent(Intent.ACTION_VIEW, uri);
		mMyActivity.startActivity(intent);
	}
	
	////////////////////////
	/// webview
	////////////////////////
    public static Object getJavaActivity() {
        return mMyActivity;
    }
    
    //WebView
    public void displayWebView(final int x, final int y, final int width, final int height) {
    	Log.i(TAG, "displayWebView");
    	this.runOnUiThread(new Runnable() {
            public void run() {
//            	LinearLayout layout = new LinearLayout(actInstance);
//            	actInstance.addContentView(layout, new LayoutParams(LayoutParams.FILL_PARENT,LayoutParams.FILL_PARENT));
            	m_webView = new WebView(mMyActivity);
            	m_webLayout.addView(m_webView);
            	
            	LinearLayout.LayoutParams linearParams = (LinearLayout.LayoutParams) m_webView.getLayoutParams();
            	linearParams.leftMargin = x;
            	linearParams.topMargin = y;
            	linearParams.width = width;
            	linearParams.height = height;
            	m_webView.setLayoutParams(linearParams);

            	m_webView.setBackgroundColor(0);
            	m_webView.getSettings().setCacheMode(WebSettings.LOAD_NO_CACHE);
            	m_webView.getSettings().setAppCacheEnabled(false);
            	//m_webView.setBackgroundResource(R.drawable.yourImage);
            	
            	m_webView.setWebViewClient(new WebViewClient(){
                    @Override
                    public boolean shouldOverrideUrlLoading(WebView view, String url){
                    	if (url.startsWith("market:")) {
                    		Uri uri = Uri.parse(url);
                    		Intent intent = new Intent(Intent.ACTION_VIEW, uri);
                    		mMyActivity.startActivity(intent);
                    		return true;
                    	}
                    	return false;
                    }
                });
            	
            }
        });
    }
    
    public void updateURL(final String url) {
    	this.runOnUiThread(new Runnable() {
            public void run() {
            	m_webView.loadUrl(url);
            }
        });
    }
    
    public void removeWebView() {
    	Log.i(TAG, "removeWebView");
    	this.runOnUiThread(new Runnable() {
            public void run() {
            	if (m_webView != null) {
            		m_webLayout.removeView(m_webView);
            		m_webView.destroy();
            	}
            }
        });
    }
}
