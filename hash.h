#pragma once 

#include <stdint.h>
#include <stdlib.h>

uint32_t jenkins_one_at_a_time_hash(const char *key, size_t len);
