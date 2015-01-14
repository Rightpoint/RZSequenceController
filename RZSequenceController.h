//
//  RZSequenceController.h
//
//  Created by Rob Visentin on 1/12/15.

// Copyright 2014 Raizlabs and other contributors
// http://raizlabs.com/
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

@import UIKit;
#import "RZSequenceChildViewController.h"

/**
 *  The direction of an RZSequenceController.
 */
typedef NS_ENUM(NSUInteger, RZSequenceDirection){
    /**
     *  The sequence pans from side to side.
     */
    RZSequenceDirectionHorizontal = 1,
    /**
     *  The sequence pans up and down.
     */
    RZSequenceDirectionVertical
};

@class RZSequenceController;

/**
 *  An RZSequenceControllerDataSource is responsible for providing an RZSequenceController with each view controller in the sequence,
 *  as well as with transitions between view controllers in the sequence.
 */
@protocol RZSequenceControllerDataSource <NSObject>

/**
 *  Returns the total number of view controlelrs in the given sequence controller.
 */
- (NSUInteger)numberOfViewControllersInSequence:(RZSequenceController *)sequenceController;

/**
 *  Returns a view controller that should appear at the given index in the sequence. 
 *  The sequence controller calls this method once when a new index in the sequence may become visible. 
 *  You can force the sequence to update its content (by calling this method) via the reloadViewControllerAtIndex(es) methods.
 *  Note that the sequence only retains the previous, current, and next view controllers in the sequence at any time.
 *
 *  @param sequenceController The sequence controller requesting the view controller.
 *  @param index              The index in the sequence that needs to be reloaded. Sequences are zero-indexed.
 */
- (UIViewController<RZSequenceChildViewController> *)sequenceController:(RZSequenceController *)sequenceController viewControllerAtIndex:(NSUInteger)index;

/**
 *  Returns the interactive transition used to transition between two view controllers in a sequence.
 *  The interactive transition is driven by scrolling that occurs in the sequence controller.
 *
 *  @param sequenceController The sequence controller requesting the transition.
 *  @param fromVC             The current view controller in the sequence.
 *  @param toVC               The view controller that will become the current view controller in the sequence when the transition is complete.
 */
- (UIPercentDrivenInteractiveTransition *)sequenceController:(RZSequenceController *)sequenceController transitionFromViewController:(UIViewController *)fromVC toViewController:(UIViewController *)toVC;

@end

/**
 *  An RZSequenceControllerDelegate receives callbacks from an RZSequenceController related to transition events in the sequence.
 */
@protocol RZSequenceControllerDelegate <NSObject>

@optional
/**
 *  Called by the sequence controller before a transition to determine whether to transition from its current view controller to the view controller at the given index.
 *
 *  @return YES if the transition should take place, and NO otherwise. If NO, the scroll view will bounce back instead of scrolling.
 */
- (BOOL)sequenceController:(RZSequenceController *)sequenceController shouldTransitionToIndex:(NSUInteger)idx;

/**
 *  Called when a transition is about to take place from the current view controller to the given view controller.
 *  At this point the currentChild and currentIndex properties of the sequence controller have not been changed.
 *
 *  @param sequenceController   The sequence controller that will perform a transition.
 *  @param child                The child that will be transitioned to.
 *  @param idx                  The index that will be transitioned to.
 *  @param animated             Whether the transition will be animated.
 */
- (void)sequenceController:(RZSequenceController *)sequenceController willTransitionToChild:(UIViewController<RZSequenceChildViewController> *)child atIndex:(NSUInteger)idx animated:(BOOL)animated;

/**
 *  Called after a transition occurs from one view controller to another.
 *  At this point the currentChild and currentIndex properties of the sequence controller have been updated.
 *
 *  @param sequenceController   The sequence controller that performed a transition.
 *  @param child                The child that was transitioned away from. This view controller may no longer be in the heirarchy.
 *  @param animated             Whether the transition was animated.
 */
- (void)sequenceController:(RZSequenceController *)sequenceController didTransitionFromChild:(UIViewController<RZSequenceChildViewController> *)child animated:(BOOL)animated;

@end

/**
 *  A view controller container that arranges child view controller in either a horizontal or vertical scrolling flow.
 *  The container managers transitions between children using UIPercentDrivenInteractiveTransitions driven by scroll events.
 */
@interface RZSequenceController : UIViewController

/**
 *  The direction of the sequence flow, either RZSequenceDirectionHorizontal or RZSequenceDirectionVertical.
 */
@property (nonatomic, readonly) RZSequenceDirection direction;

/**
 *  The currently displayed index in the sequence. You can KVO this property or provide an RZSequenceControllerDelegate
 *  to receive callbacks when this property changes.
 */
@property (assign, nonatomic, readonly) NSUInteger currentIndex;

/**
 *  The current view controller in the sequence, shown on screen.
 */
@property (strong, nonatomic, readonly) UIViewController<RZSequenceChildViewController> *currentChild;

/**
 *  The previous view controller in the sequence, either to the left of the current child (horiztonal sequence) or above it (vertical sequence).
 */
@property (strong, nonatomic, readonly) UIViewController<RZSequenceChildViewController> *previousChild;

/**
 *  The next view controller in the sequence, either to the right of the current child (horiztonal sequence) or below it (vertical sequence).
 */
@property (strong, nonatomic, readonly) UIViewController<RZSequenceChildViewController> *nextChild;

/**
 *  The percentage complete of the current transition between two children, or 0.0 if no transition is taking place.
 *  KVO compliant.
 */
@property (assign, nonatomic, readonly) CGFloat transitionPercentage;

/**
 *  @see RZSequenceControllerDataSource
 */
@property (weak, nonatomic) id<RZSequenceControllerDataSource> dataSource;

/**
 *  @see RZSequenceControllerDelegate
 */
@property (weak, nonatomic) id<RZSequenceControllerDelegate> delegate;

/**
 *  Initialize a new sequence controller with the given direction.
 */
- (instancetype)initWithDirection:(RZSequenceDirection)direction;

/**
 *  Reloads the view controller at the given index. If idx is invalid or not one of the previous, current, or next indexes, this method does nothing.
 *  @see reloadViewControllersAtIndexes:
 */
- (void)reloadViewControllerAtIndex:(NSUInteger)idx;

/**
 *  Reloads the view controllers at the given indexes.
 *  Indexes that are invalid or not one of the previous, current, or next indexes are ignored.
 */
- (void)reloadViewControllersAtIndexes:(NSIndexSet *)indexes;

/**
 *  Force a transition to the given index in the sequence. By default this method calls
 *  @code [self transitionToIndex:idx animated:animated skipIntermediateViews:NO] @endcode
 */
- (void)transitionToIndex:(NSUInteger)idx animated:(BOOL)animated;

/**
 *  Force a transition to the given index in the sequence.
 *
 *  @param idx      The index to transition to in the sequence.
 *  @param animated Whether the transition should be animated.
 *  @param skip     Whether views in between the current index and idx should be skipped. For example, if skip = YES,
 *                  Then transitioning from index 1 to 4 would NOT transition from 1-2-3-4, but instead perform a transtion from 1-4 directly.
 */
- (void)transitionToIndex:(NSUInteger)idx animated:(BOOL)animated skipIntermediateViews:(BOOL)skip;

@end

@interface UIViewController (RZSequenceController)

/**
 *  The nearest ancestor in the view controller hierarchy that is a sequence controller, or nil if none exists.
 */
@property (nonatomic, readonly) RZSequenceController *sequenceController;

@end
