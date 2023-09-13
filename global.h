#ifndef GLOBAL_H
#define GLOBAL_H

#include "admin.h"
#include "member.h"
#include "fitness.h"

void logOut(bool& access, int& id, string& category, string& username);
int auth(bool& access, string& category, string& username, Admin* admin[], Member* member[], Admin adminN, Member memberR);
void quitProgram(int& id, bool& access, Admin* admin[], Member* member[], Fitness* fitness[], Admin adminN, Member memberR, Fitness fitnessS);

#endif