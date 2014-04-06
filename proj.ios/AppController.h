#import <UIKit/UIKit.h>

#define MY_BANNER_UNIT_ID @"ca-app-pub-6202650789898961/9240457647"

@class RootViewController;

extern "C"{
#import "GADBannerView.h"
};

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADBannerView *bannerView_;
}
@property (nonatomic, strong)   UIView *adView1;
@end

