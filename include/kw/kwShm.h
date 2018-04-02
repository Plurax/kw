/*
 * kwShm.h
 *
 *  Created on: 27.01.2014
 *      Author: chuhlich
 */

#ifndef KWSHM_H_
#define KWSHM_H_

#include "kw/kwDataSource.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class kwShm : public kwDataSource
{
 public:
  kwShm(json configuration);

  void init();
  void deInit();

  char* getPtr();
  bool lockSegment();
  bool unlockSegment();
  bool isLocked();
 private:
  key_t m_shmid;
  int m_semid;
  size_t m_size;
  char  *m_segptr;
};

#endif /* KWSHM_H_ */
