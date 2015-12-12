# CatOS's memory management

## How to include *Aegen* to project
add fellowing lines to your source file:

```
#include "sysInfo.h"
#include "memPool.h"
```

then, initialize the pool by using:

```
void *p = malloc(SIZE);
sysInfoConfig(p, SIZE);
memPoolConfig();
```

for more information, please reference to *test.c*

## How to contribute to this project
feel free to send pull requests

## Author's Information
 Created by @Zhang Shihai
