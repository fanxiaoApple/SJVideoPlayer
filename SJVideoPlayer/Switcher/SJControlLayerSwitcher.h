//
//  SJControlLayerSwitcher.h
//  SJVideoPlayerProject
//
//  Created by 畅三江 on 2018/6/1.
//  Copyright © 2018年 畅三江. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SJControlLayerDefines.h"
#if __has_include(<SJBaseVideoPlayer/SJBaseVideoPlayer.h>)
#import <SJBaseVideoPlayer/SJBaseVideoPlayer.h>
#else
#import "SJBaseVideoPlayer.h"
#endif
@protocol SJControlLayerSwitcherObsrever, SJControlLayerSwitcherDelegate;

NS_ASSUME_NONNULL_BEGIN
extern SJControlLayerIdentifier SJControlLayer_Uninitialized;

/// - 控制层切换器 switcher -
///
/// - 使用示例请查看`SJVideoPlayer`的`init`方法.
@protocol SJControlLayerSwitcher <NSObject>
- (instancetype)initWithPlayer:(__weak SJBaseVideoPlayer *)player;

/// 切换控制层
///
/// - 将当前的控制层切换为指定标识的控制层
- (void)switchControlLayerForIdentitfier:(SJControlLayerIdentifier)identifier;
- (BOOL)switchToPreviousControlLayer;

/// 添加或替换原有控制层
///
/// - 控制层将在第一次切换时创建, 该控制层只会被创建一次
- (void)addControlLayerForIdentifier:(SJControlLayerIdentifier)identifier
                         lazyLoading:(nullable id<SJControlLayer>(^)(SJControlLayerIdentifier identifier))loading;

/// 删除控制层
- (void)deleteControlLayerForIdentifier:(SJControlLayerIdentifier)identifier;

/// 是否已存在
- (BOOL)containsControlLayer:(SJControlLayerIdentifier)identifier;

/// 获取某个控制层
///
/// - 如果不存在, 将返回 nil
- (nullable id<SJControlLayer>)controlLayerForIdentifier:(SJControlLayerIdentifier)identifier;

/// 获取一个切换器观察者
///
/// - 你需要对它强引用, 否则会被释放
- (id<SJControlLayerSwitcherObsrever>)getObserver;

@property (nonatomic, weak, nullable) id<SJControlLayerSwitcherDelegate> delegate;
@property (nonatomic, readonly) SJControlLayerIdentifier previousIdentifier;
@property (nonatomic, readonly) SJControlLayerIdentifier currentIdentifier;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end


@interface SJControlLayerSwitcher : NSObject<SJControlLayerSwitcher>

@end

@protocol SJControlLayerSwitcherDelegate <NSObject>
@optional
- (BOOL)switcher:(id<SJControlLayerSwitcher>)switcher shouldSwitchToControlLayer:(SJControlLayerIdentifier)identifier;
@end

// - observer -
@protocol SJControlLayerSwitcherObsrever <NSObject>
@property (nonatomic, copy, nullable) void(^playerWillBeginSwitchControlLayer)(id<SJControlLayerSwitcher> switcher, id<SJControlLayer> controlLayer);
@property (nonatomic, copy, nullable) void(^playerDidEndSwitchControlLayer)(id<SJControlLayerSwitcher> switcher, id<SJControlLayer> controlLayer);
@end
NS_ASSUME_NONNULL_END



#import "SJControlLayerCarrier.h"
NS_ASSUME_NONNULL_BEGIN
// - deprecated
@interface SJControlLayerSwitcher (Deprecated)
- (void)switchControlLayerForIdentitfier:(SJControlLayerIdentifier)identifier
                           toVideoPlayer:(__kindof SJBaseVideoPlayer *)videoPlayer __deprecated_msg("use `switchControlLayerForIdentitfier`;");
- (void)addControlLayer:(SJControlLayerCarrier *)carrier __deprecated_msg("use `addControlLayerForIdentifier:lazyLoading`;");
@end
NS_ASSUME_NONNULL_END
