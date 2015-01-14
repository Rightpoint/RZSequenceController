//
//  RZSequenceChildViewController.h
//
//  Created by Rob Visentin on 1/13/15.

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

/**
 *  View controllers must conform to this protocol in order to be added to an RZSequenceController.
 *  @see RZSequenceController
 */
@protocol RZSequenceChildViewController <NSObject>

/**
 *  The scroll view that should drive forward or backward movement in an RZSequenceController.
 *  If the view controller has a full-screen scroll view, it should be returned by this method.
 *  Otherwise, you may return nil, in which case the RZSequenceController will take care of panning the sequence.
 */
@property (nonatomic, readonly) UIScrollView *rzq_contentScrollView;

@end
