#import "NativeBridge.h"

const char* NativeBridge::getLocalizeString(const char *key)
{
    NSString* nsStringKey = [NSString stringWithCString: key encoding:NSUTF8StringEncoding];
    return [NSLocalizedString(nsStringKey, nil) UTF8String];
}
