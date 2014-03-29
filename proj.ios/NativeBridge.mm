#import "NativeBridge.h"
#import <Twitter/Twitter.h>
#import <Social/Social.h>

USING_NS_CC;

const char* NativeBridge::getLocalizeString(const char *key)
{
    NSString* nsStringKey = [NSString stringWithCString: key encoding:NSUTF8StringEncoding];
    return [NSLocalizedString(nsStringKey, nil) UTF8String];
}

void NativeBridge::openTweetDialog(int score)
{
    NSString* tweet = [NSString stringWithFormat:NSLocalizedString(@"Tweet", nil), score];
    if([TWTweetComposeViewController canSendTweet]){
        UIViewController *myViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
        TWTweetComposeViewController *twitterVC = [[TWTweetComposeViewController alloc]init];
        [twitterVC setInitialText: tweet];
        
        twitterVC.completionHandler = ^(TWTweetComposeViewControllerResult res){
            [myViewController dismissViewControllerAnimated:YES completion: nil];
        };
        
        // URLを追加(アプリのストアURL)
        [twitterVC addURL:[NSURL URLWithString:NSLocalizedString(@"AppUrl", nil)]];
        
        [myViewController presentViewController: twitterVC animated:YES completion: nil];
    }else{
        tweet = [NSString stringWithFormat: @"%@%@",@"http://twitter.com/intent/tweet?text=",tweet];
        tweet = [tweet stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        [[UIApplication sharedApplication]openURL:[NSURL URLWithString:tweet]];
    }
    tweet = nil;
}

void NativeBridge::openFacebookDialog(int score)
{
    SLComposeViewController *composeViewController = [SLComposeViewController
                                                      composeViewControllerForServiceType:SLServiceTypeFacebook];
    
    //デフォルトメッセージ　ハッシュタグ付き
    NSString* facebookSend = [NSString stringWithFormat:NSLocalizedString(@"FaceBookSend", nil), score];
    [composeViewController setInitialText:facebookSend];
    
    // URLを追加(アプリのストアURL)
    [composeViewController addURL:[NSURL URLWithString:NSLocalizedString(@"AppUrl", nil)]];

    UIViewController *myViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    [myViewController presentViewController: composeViewController animated:NO completion: nil];
}