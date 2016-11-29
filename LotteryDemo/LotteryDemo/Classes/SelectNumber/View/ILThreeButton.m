
#import "ILThreeButton.h"

@interface ILThreeButton()
- (IBAction)selectType;
- (IBAction)selectCount;
- (IBAction)selectCategory;
@end

@implementation ILThreeButton

+ (instancetype)threeButton
{
    return [[NSBundle mainBundle] loadNibNamed:@"ILThreeButton" owner:nil options:nil][0];
}

- (IBAction)selectType {
}

- (IBAction)selectCount {
}

- (IBAction)selectCategory {
}
@end
