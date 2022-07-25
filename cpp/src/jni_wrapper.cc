/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>
#include <iostream>



#ifdef __cplusplus
extern "C" {
#endif

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv *env;
	if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_10) != JNI_OK) {
		return JNI_ERR;
	}
	std::cout << "Loaded Velox backend." << std::endl;
	return env->GetVersion();
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
	JNIEnv *env;
	std::cout << "Loaded Velox backend." << std::endl;
}


}