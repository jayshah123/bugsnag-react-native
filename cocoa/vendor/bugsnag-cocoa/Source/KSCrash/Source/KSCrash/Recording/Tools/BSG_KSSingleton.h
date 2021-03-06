//
//  KSSingleton.h
//
//  Created by Karl Stenerud on 2013-02-10.
//
//  Copyright (c) 2012 Karl Stenerud. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall remain in place
// in this source code.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef HDR_BSG_KSSingleton_h
#define HDR_BSG_KSSingleton_h

/** Create a "sharedInstance" method with the specified type.
 *
 * @param TYPE The type to return from "sharedInstance".
 */
#define IMPLEMENT_SHARED_INSTANCE(TYPE) \
+ (TYPE*) sharedInstance \
{ \
    static id sharedInstance = nil; \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^ \
    { \
        sharedInstance = [[self alloc] init]; \
    }); \
    return sharedInstance; \
}


/** Create an exclusive "sharedInstance" method with the specified type.
 * This will also implement "allocWithZone:" and actively prohibit multiple
 * instances from existing.
 *
 * Note: This won't stop someone from manually creating an instance BEFORE
 * sharedInstance is called, but if that does happen, you'll still see a failed
 * alloc.
 *
 * @param TYPE The type to return from "sharedInstance".
 */
#define IMPLEMENT_EXCLUSIVE_SHARED_INSTANCE(TYPE) \
IMPLEMENT_SHARED_INSTANCE(TYPE) \
 \
+ (id) allocWithZone:(NSZone *)zone \
{ \
    @synchronized(self) \
    { \
        static id singleInstance = nil; \
        if(singleInstance != nil) \
        { \
            NSLog(@"Error: Only one instance allowed. Use [%@ sharedInstance] to access it", self); \
            return nil; \
        } \
        singleInstance = [super allocWithZone:zone]; \
        return singleInstance; \
    } \
}


#endif // HDR_KSSingleton_h
