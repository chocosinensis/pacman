void FilePath(char *path, char *filename) {
  const char *dirname = "logs";

  // INFO: CHECKING IF THE `./logs` DIRECTORY EXISTS, OTHERWISE mkdir
  struct stat statbuf;
  if (stat(dirname, &statbuf) != 0)
    if (mkdir(dirname, 0755) != 0) return;

  sprintf(path, "./%s/%s.log", dirname, filename);
}

bool LogFileExists(char *filename) {
  char path[MAX_PATH_LENGTH] = { 0 };
  FilePath(path, filename);

  FILE *file = fopen(path, "r");
  if (file == NULL) return false;

  fclose(file);
  return true;
}

bool ReadFile(char *filename, char *data) {
  char path[MAX_PATH_LENGTH] = { 0 };
  FilePath(path, filename);

  FILE *file = fopen(path, "r");
  if (file == NULL) return false;

  char buffer[2048] = { 0 };
  while (fgets(buffer, sizeof(buffer), file) != NULL) strcat(data, buffer);

  fclose(file);
  return true;
}

bool WriteFile(char *filename, char *data) {
  char path[MAX_PATH_LENGTH];
  FilePath(path, filename);

  FILE *file = fopen(path, "w");
  if (file == NULL) return false;

  fprintf(file, "%s", data);

  fclose(file);
  return true;
}

bool GetNames(char namesList[MAX_NAMES][MAX_NAME_LENGTH]) {
  char names[FILE_SIZE] = { 0 };
  bool fileExists = ReadFile(NAMES_LIST, names);
  if (!fileExists) return fileExists;

  int i = 0;
  char *token = strtok(names, "\n");

  while (token != NULL) {
    for (int j = 0; j < strlen(token); j++)
      namesList[i][j] = token[j];
    token = strtok(NULL, "\n");
    i++;
    if (token != NULL && i > MAX_NAMES) break;
  }
  return true;
}

bool SortNames() {
  char namesList[MAX_NAMES][MAX_NAME_LENGTH];
  for (int i = 0; i < MAX_NAMES; i++) for (int j = 0; j < MAX_NAME_LENGTH; j++) namesList[i][j] = 0;
  GetNames(namesList);

  int n = 0;
  for (int i = 0; i < MAX_NAMES; i++) {
    if (*namesList[i] == '\0') break;
    n++;
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      Player p, p1;
      ReadPlayerDetails(namesList[j], &p);
      ReadPlayerDetails(namesList[j + 1], &p1);

      bool condition = p.level < p1.level
        || (p.level == p1.level && p.highScore < p1.highScore)
        || (p.level == p1.level && p.highScore == p1.highScore && p.elapsedTime > p1.elapsedTime);

      if (condition) {
        char tmp[MAX_NAME_LENGTH] = { 0 };
        strcpy(tmp, namesList[j]);
        strcpy(namesList[j], namesList[j + 1]);
        strcpy(namesList[j + 1], tmp);
      }
    }
  }

  char data[FILE_SIZE] = { 0 };
  for (int k = 0; k <= n; k++) {
    strcat(data, namesList[k]);
    if (k != n) strcat(data, "\n");
  }
  return WriteFile(NAMES_LIST, data);
}

bool IsNameInList(char *name) {
  char namesList[MAX_NAMES][MAX_NAME_LENGTH];
  for (int i = 0; i < MAX_NAMES; i++) for (int j = 0; j < MAX_NAME_LENGTH; j++) namesList[i][j] = 0;
  GetNames(namesList);

  for (int i = 0; i < MAX_NAMES; i++) {
    if (*namesList[i] == '\0') break;
    if (strcmp(name, namesList[i]) == 0) return true;
  }
  return false;
}

bool AddName(char *name) {
  if (IsNameInList(name)) return false;
  if (strlen(name) > MAX_NAME_LENGTH) return false;

  char namesList[MAX_NAMES][MAX_NAME_LENGTH];
  for (int i = 0; i < MAX_NAMES; i++) for (int j = 0; j < MAX_NAME_LENGTH; j++) namesList[i][j] = 0;
  GetNames(namesList);

  int i = 0;
  for (; i < MAX_NAMES; i++)
    if (*namesList[i] == '\0') break;

  if (i == MAX_NAMES) {
    RemovePlayer(namesList[MAX_NAMES - 1]);
    i--;
  }
  if (i > MAX_NAMES) return false;

  for (int j = 0; j < strlen(name); j++) {
    namesList[i][j] = name[j];
  }

  char data[FILE_SIZE] = { 0 };
  for (int k = 0; k <= i; k++) {
    strcat(data, namesList[k]);
    if (k != i) strcat(data, "\n");
  }
  return WriteFile(NAMES_LIST, data);
}

bool RemoveName(char *name) {
  bool isNameInList = IsNameInList(name);
  if (!isNameInList) return false;

  char namesList[MAX_NAMES][MAX_NAME_LENGTH];
  for (int i = 0; i < MAX_NAMES; i++) for (int j = 0; j < MAX_NAME_LENGTH; j++) namesList[i][j] = 0;
  GetNames(namesList);

  char newList[MAX_NAMES][MAX_NAME_LENGTH];
  for (int i = 0; i < MAX_NAMES; i++) for (int j = 0; j < MAX_NAME_LENGTH; j++) newList[i][j] = 0;

  int idx = 0;
  for (int i = 0; i < MAX_NAMES; i++) {
    if (*namesList[i] == '\0') break;
    if (strcmp(name, namesList[i]) == 0) continue;
    char *s = namesList[i];
    for (int j = 0; j < strlen(s); j++)
      newList[idx][j] = s[j];
    idx++;
  }

  char data[FILE_SIZE] = { 0 };
  for (int k = 0; k <= idx; k++) {
    strcat(data, newList[k]);
    if (k != idx) strcat(data, "\n");
  }
  return WriteFile(NAMES_LIST, data);
}

Player InitPlayer(char *name) {
  Player player = { 0 };
  bool fileExists = ReadPlayerDetails(name, &player);
  if (fileExists) return player;
  player.name = name;
  NullifyPlayerDetails(&player);
  return player;
}

bool RemovePlayer(char *name) {
  bool removeName = RemoveName(name);
  if (!removeName) return removeName;

  char path[MAX_PATH_LENGTH];
  FilePath(path, name);
  return remove(path) == 0;
}

bool ReadPlayerDetails(char *name, Player *player) {
  char data[MAX_CHARS] = { 0 };
  bool fileExists = ReadFile(name, data);
  if (!IsNameInList(name) || !fileExists) return false;

  char playerName[MAX_NAME_LENGTH] = { 0 };
  int level = 0;
  int highScore = 0;
  int lastLevelScore = 0;
  double elapsedTime = 0;
  int lives = 0;

  sscanf(data, PLAYER_DETAILS_TEMPLATE, playerName, &level, &highScore, &lastLevelScore, &lives, &elapsedTime);

  player->name = name;
  player->level = level;
  player->highScore = highScore;
  player->lastLevelScore = lastLevelScore;
  player->elapsedTime = elapsedTime;
  player->lives = lives;

  return true;
}

bool WritePlayerDetails(Player player) {
  if (!IsNameInList(player.name)) AddName(player.name);
  if (IsNameInList(player.name)) SortNames();

  char details[MAX_CHARS];
  sprintf(
    details, PLAYER_DETAILS_TEMPLATE,
    player.name, player.level, player.highScore, player.lastLevelScore, player.lives, player.elapsedTime
  );
  return WriteFile(player.name, details);
}

bool NullifyPlayerDetails(Player *player) {
  player->level = 1;
  player->highScore = 0;
  player->lastLevelScore = 0;
  player->elapsedTime = 0;
  player->lives = MAX_LIVES;

  return WritePlayerDetails(*player);
}
