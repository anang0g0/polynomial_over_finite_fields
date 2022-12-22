static const unsigned short gf[512]={0,1,2,4,8,16,32,64,128,256,17,34,68,136,272,49,98,196,392,257,19,38,76,152,304,113,226,452,409,291,87,174,348,169,338,181,362,197,394,261,27,54,108,216,432,369,243,486,477,427,327,159,318,109,218,436,377,227,454,413,299,71,142,284,41,82,164,328,129,258,21,42,84,168,336,177,354,213,426,325,155,310,125,250,500,505,483,471,447,367,207,414,301,75,150,300,73,146,292,89,178,356,217,434,373,251,502,509,491,455,415,303,79,158,316,105,210,420,345,163,326,157,314,101,202,404,313,99,198,396,265,3,6,12,24,48,96,192,384,273,51,102,204,408,289,83,166,332,137,274,53,106,212,424,321,147,294,93,186,372,249,498,501,507,487,479,431,335,143,286,45,90,180,360,193,386,277,59,118,236,472,417,339,183,366,205,410,293,91,182,364,201,402,309,123,246,492,457,387,279,63,126,252,504,481,467,439,383,239,478,429,331,135,270,13,26,52,104,208,416,337,179,358,221,442,357,219,438,381,235,470,445,363,199,398,269,11,22,44,88,176,352,209,418,341,187,374,253,506,485,475,423,351,175,350,173,346,165,330,133,266,5,10,20,40,80,160,320,145,290,85,170,340,185,370,245,490,453,411,295,95,190,380,233,466,437,379,231,462,397,267,7,14,28,56,112,224,448,401,307,119,238,476,425,323,151,302,77,154,308,121,242,484,473,419,343,191,382,237,474,421,347,167,334,141,282,37,74,148,296,65,130,260,25,50,100,200,400,305,115,230,460,393,259,23,46,92,184,368,241,482,469,443,359,223,446,365,203,406,317,107,214,428,329,131,262,29,58,116,232,464,433,371,247,494,461,395,263,31,62,124,248,496,497,499,503,511,495,463,399,271,15,30,60,120,240,480,465,435,375,255,510,493,459,391,287,47,94,188,376,225,450,405,315,103,206,412,297,67,134,268,9,18,36,72,144,288,81,162,324,153,306,117,234,468,441,355,215,430,333,139,278,61,122,244,488,449,403,311,127,254,508,489,451,407,319,111,222,444,361,195,390,285,43,86,172,344,161,322,149,298,69,138,276,57,114,228,456,385,275,55,110,220,440,353,211,422,349,171,342,189,378,229,458,389,283,39,78,156,312,97,194,388,281,35,70,140,280,33,66,132,264};
static const unsigned short fg[512]={0,1,2,131,3,261,132,291,4,421,262,236,133,214,292,391,5,10,422,20,263,70,237,344,134,333,215,40,293,366,392,378,6,508,11,504,423,326,21,496,264,64,71,463,238,170,345,406,135,15,334,140,216,150,41,480,294,474,367,177,393,442,379,200,7,330,509,418,12,471,505,61,424,96,327,93,22,307,497,112,265,427,65,145,72,270,464,30,239,99,171,188,346,157,407,280,136,500,16,127,335,123,141,414,217,115,151,360,42,53,481,456,295,25,475,339,368,432,178,300,394,310,443,194,380,82,201,449,8,68,331,364,510,259,419,212,13,148,472,440,506,324,62,168,425,268,97,155,328,469,94,305,23,430,308,80,498,121,113,51,266,467,428,119,66,257,146,322,73,33,271,488,465,255,31,253,240,75,100,221,172,35,189,183,347,273,158,245,408,490,281,316,137,174,501,460,17,37,128,233,336,191,124,357,142,185,415,90,218,242,116,485,152,77,361,437,43,102,54,226,482,223,457,354,296,410,26,57,476,492,340,287,369,283,433,229,179,318,301,208,395,349,311,46,444,275,195,373,381,160,83,105,202,247,450,400,9,19,69,343,332,39,365,377,511,130,260,290,420,235,213,390,14,139,149,479,473,176,441,199,507,503,325,495,63,462,169,405,426,144,269,29,98,187,156,279,329,417,470,60,95,92,306,111,24,338,431,299,309,193,81,448,499,126,122,413,114,359,52,455,267,154,468,304,429,79,120,50,67,363,258,211,147,439,323,167,74,220,34,182,272,244,489,315,466,118,256,321,32,487,254,252,241,484,76,436,101,225,222,353,173,459,36,232,190,356,184,89,348,45,274,372,159,104,246,399,409,56,491,286,282,228,317,207,138,478,175,198,502,494,461,404,18,342,38,376,129,289,234,389,337,298,192,447,125,412,358,454,143,28,186,278,416,59,91,110,219,181,243,314,117,320,486,251,153,303,78,49,362,210,438,166,44,371,103,398,55,285,227,206,483,435,224,352,458,231,355,88,297,446,411,453,27,277,58,109,477,197,493,403,341,375,288,388,370,397,284,205,434,351,230,87,180,313,319,250,302,48,209,165,396,204,350,86,312,249,47,164,445,452,276,108,196,402,374,387,382,383,161,384,84,162,106,385,203,85,248,163,451,107,401,386};
