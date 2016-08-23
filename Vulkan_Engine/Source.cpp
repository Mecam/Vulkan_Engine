#include "EG_Engine.h"

egEngine engine;

void main()
{
	engine.run();
}

/*
Globals:	eg...
Members:	m...
arguments:	a...
else:		v...
*/

/*
Using Git

Adding a feature:
	1. Create a local "feature_name" branch of off the development branch
	2. Commit files/code relating to that feature to that branch
	3. Once done, merge the feature branch with the development branch
	4. Push the development branch to origin
	E. If a feature added by another contributor causes a merge/push conflict:
		1. Pull the modified development branch from origin
		2. Rebase your feature branch onto the updated development branch
		3. Repeat steps 3-4

Preparing a release:
	1. Create a local "release" branch of off the development branch
	2. Integrate any new features added since the last release into the program and commit the changes to the release branch
	3. Merge the release branch with the local master branch
	4. Push the master branch to origin

*/
