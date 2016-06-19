#include "shared.h"
/*
 Compare two version numbers version1 and version2.
 If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.
 
 You may assume that the version strings are non-empty and contain only digits and the . character.
 The . character does not represent a decimal point and is used to separate number sequences.
 For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.
 
 Here is an example of version numbers ordering:
 
 0.1 < 1.1 < 1.2 < 13.37
*/
namespace CompareVersionNumbers {
    class Solution {
    public:
        int compareVersion(string version1, string version2) {
            int start1 = 0, start2 = 0;
            while(start1 < version1.length() && start2 < version2.length()){
                auto v1 = nextVersion(version1, start1);
                auto v2 = nextVersion(version2, start2);
                start1 = v1.second;
                start2 = v2.second;
                if(v1.first < v2.first)
                    return -1;
                if(v1.first > v2.first)
                    return 1;
            }
            if(start1 == version1.length() && start2 == version2.length())
                return 0;
            if(start1 == version1.length()){
                while(start2 < version2.length()){
                    auto v2 = nextVersion(version2, start2);
                    if(v2.first != 0)
                        return -1;
                    start2 = v2.second;
                }
                return 0;
            }
            while(start1 < version1.length()){
                auto v1 = nextVersion(version1, start1);
                if(v1.first != 0)
                    return 1;
                start1 = v1.second;
            }
            return 0;
        }
    private:
        pair<int,int> nextVersion(string& version, int start){
            if(start >= version.length())
                return {-1, version.length()};
            int i = start, result = 0;
            for(; i < version.length(); ++ i){
                if(version[i] == '.')
                    return {result, i + 1};
                result *= 10;
                result += (version[i] - '0');
            }
            return{result, i};
        }
    };
}
