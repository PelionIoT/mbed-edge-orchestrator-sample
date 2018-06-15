/**
 * @file    main.cpp
 * @brief   mbed Edge Orchestrator Sample - main entry
 * @author  Doug Anson
 * @version 1.0
 * @see     
 *
 * Copyright (c) 2018
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Sample Non-Mbed Device
#include "NonMbedDevice.h"

// Orchestrator to PT
#include "Orchestrator.h"

// Utils
#include "utils.h"

// main entry point
int main(int argc, char **argv)
{
	// setup our signals
	setup_signals();

	// Simulated Trival device: generates a "pulse" value every "n" seconds and has a gettable/settable switch state
	NonMbedDevice *non_mbed_device = new NonMbedDevice();
	if (non_mbed_device != NULL) {
		// create our orchestrator for interacting via PT with mbed-edge
        	Orchestrator *orchestrator = new Orchestrator(non_mbed_device);

		// register our device "tick" handler
		non_mbed_device->setEventCallbackHandler(Orchestrator::tickHandler,(void *)orchestrator);

	        // start the simulated device
		printf("Main: starting the trivial device...\n");
	        non_mbed_device->start();

		// next we connect our orchestrator to mbed edge via PT...
		if (orchestrator->connectToMbedEdgePT(argc,argv) == true) {
		    // we are connected to mbed-edge via PT... so start the orchestrator event loop
		    orchestrator->processEvents();
		}
		else {
		    // unable to bind to mbed-edge via PT... so exit
		    printf("Main: ERROR: Unable to bind to mbed-edge via PT. Exiting...\n");
		}
	}

	// we reached the end... 
	printf("Main: processing has ended!. Exiting...\n");
}