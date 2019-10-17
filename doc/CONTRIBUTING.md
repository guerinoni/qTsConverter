# COMMIT
All rules are based on: https://chris.beams.io/posts/git-commit/

If a single commit close a story or bug or task insert in commit message `<PROJECT>-<TASK_ID>` (i.e. `ACTO-30: Fix some stuff`) else include this tag in the last commit or in merge commit.

# VERSIONING
All rules are based on: https://semver.org/

# BRANCHING
There are always `master` and `develop` branch. In `master` there are only
release version with `tag` of the version, instead in `develop` there is only
the middle version of the sprints. Every sprints all developers start from
`develop` and create their own branch regarding the `story`. For every feature
we can use /feature/branch-name (i.e. `feature/iot-download-photo`) for bugfix
task we can use /bugfix (i.e. `bugfix/searching-crash`). When the story is
completed you can create a `pull request` for this branch and other developer
will review the code before merging all in a code review session.
If more than one developer working of the same story the owner of story create
the "main" branch for the story and merge other sub-branch before create final
`pull-request`


# CODE Guidelines
In the root folder of the project, there is .clang-format, to enable formatting code with this rules you must install clang-format package (i.e. sudo apt install clang-format6) and set in qt-creator (or other editors) to use "file" options and automatically you IDE take clang file in root folder.

### C++ code
The main rule is to keep separate logic code from GUI code and the best solution is to use Qt classes only for GUI purpose and for rest of the code use Standard Library. There is a skeleton repo with a lot of reusable modules. If you find a bug or enhancement please contact the maintainers.
For the rest of the code:
- file *.hpp and *.cpp
- use `#pragma once` instead include guard
- use `struct` only for passive object
- follow `SOLID` principle
- `Capitalize` class and rest in `snake_case`
- private member variable with trailing underscore (i.e. `var_`)
- simple function for getter and setter `var()` - `set_var(type value)`

### QML code
For this language there aren't strict rules but please: 
- keep single component in separated file
- groups subproperties (i.e. `font { pixelSize:33 ... }` )
- put `id` property only if other obj need to call it
- the best order for property is:
    * `id`
    * `property` definition
    * `signal` definition
- in property definition if no default value is provided means that property is set from outside, instead if default value is provided means that property is used in local file
- use `camelCase` for all declared in qml
