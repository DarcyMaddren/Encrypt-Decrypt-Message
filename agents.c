#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// Common declarations
#define MAX_TEXTFILE_SIZE       4096
#define MAX_FILENAME_LENGTH       80
#define MAX_NUMBER_AGENTS         15
#define MAX_AGENTNAME_LENGTH      45
#define MAX_LINE_LENGTH           96

typedef struct {
    char name[MAX_AGENTNAME_LENGTH];
    size_t key;
} Agent;

typedef struct {
    size_t size;
    size_t next;
    Agent  pool[MAX_NUMBER_AGENTS];
} AgentPool;

void encryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength);
void decryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength);

size_t readText(FILE* file, char text[], size_t maxTextSize);
size_t readCipherBook(FILE* file, char text[], size_t maxTextSize);
size_t readMessage(FILE* file, char text[], size_t maxTextSize);

void initAgentPool(AgentPool* agentPool);
Agent* newAgent(AgentPool* agentPool);
void deleteAgent(Agent* agent, AgentPool* agentPool);
Agent* readAgent(FILE* file, AgentPool* agentPool);
Agent* findAgent(char name[], AgentPool* agentPool);
void readAgentName(char agentName[], size_t maxAgentNameLength);

int main(void)
{
    //char filename[80] = "";
    char agentname[MAX_AGENTNAME_LENGTH] = "";
    FILE* file = NULL;
    char book[MAX_TEXTFILE_SIZE] = "";
    char message[MAX_TEXTFILE_SIZE] = "";
    size_t bookLength = 0;
    size_t messageLength = 0;
    AgentPool agentPool;
    Agent* agent = NULL;

    // Read in the cipher book
    scanf("%80s", filename);
    file = fopen("iliad.txt", "r");
    if (file == NULL) {
        printf("File not found... program will fail with segmentation fault\n");
    }
    bookLength = readCipherBook(file, book, MAX_TEXTFILE_SIZE);
    fclose(file);

    // Read in the message
    scanf("%80s", filename);
    file = fopen("studentcipherbook.txt", "r");
    if (file == NULL) {
        printf("File not found... program will fail with segmentation fault\n");
    }
    messageLength = readMessage(file, message, MAX_TEXTFILE_SIZE);
    fclose(file);

    scanf("%80s", filename);
    initAgentPool(&agentPool);
    file = fopen("agents.txt", "r");
    if (file == NULL) {
        printf("File not found... program will fail with segmentation fault\n");
    }
    while (!feof(file)) {
        readAgent(file, &agentPool);
    }
    fclose(file);

    getchar();
    readAgentName(agentname, MAX_AGENTNAME_LENGTH);
    agent = findAgent("Maxwell Smart", &agentPool);
    if (agent != NULL) {
        encryptMessage(book, bookLength, agent, message, messageLength);
        printf("Secret message is: ");
        for(size_t i=0; i < messageLength; i++) {
            printf(" %d", message[i]);
        }
        decryptMessage(book, bookLength, agent, message, messageLength);
        printf("\nDecrypted message is: %s\n", message);
    } else {
        printf("No Agent found by the name %s\n", agentname);
    }
    return 0;
}

// Book in form 'thisisacipherbook' (no spaces).
// Message in form '09 39 42 12 58 48 42 48' (encripted).
void encryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength)
{
    size_t key = agent->key;
    size_t c;

    for (size_t i = 0; i < messageLength; i++) {
        c = book[(i + key) % bookLength];
        message[i] = (message[i] + c) % 98;
    }
}

void decryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength)
{
    size_t key = agent->key % bookLength;

    for (size_t i = 0; i < messageLength; i++) {
        message[i] -= book[key % bookLength];

        while (message[i] < 0) {
            message[i] += 98;
        }

        if (message[i] == 96) {
            message[i] = '\t';
        } else if (message[i] == 97) {
            message[i] = '\n';
        } else {
            message[i] += 31;
        }
        key++;
    }
}

size_t readText(FILE* file, char text[], size_t maxTextSize)
{
    int c;
    int count = 0;
    while ((c = fgetc(file)) != EOF && count < maxTextSize - 1) {
        text[count] = c;
        count++;
    }
    text[count] = '\0';
    return count;
}

size_t readCipherBook(FILE* file, char text[], size_t maxTextSize)
{
    size_t textLength = readText(file, text, maxTextSize);
    size_t count = 0;
    char* out = text;

    for (size_t i = 0; i < textLength; i++) {
        if (!isspace(text[i])) {
            out[count++] = text[i];
        }
    }
    out[count] = '\0';
    return count;
}

size_t readMessage(FILE* file, char text[], size_t maxTextSize)
{
    size_t textLength = readText(file, text, maxTextSize);
    char *out = text;
    int count = 0;

    for (size_t i = 0; i < maxTextSize-1 && i < textLength; i++) {
        if (text[i] == '\t') {
            out[i] = 96;
        } else if (text[i] == '\n') {
            out[i] = 97;
        } else {
            out[i] = (int)(text[i] - 31);
        } count++;
    }
    out[count] = '\0';
    return count;
}

// A function to initialise an AgentPool structure
void initAgentPool(AgentPool* agentPool)
{
    agentPool->size = MAX_NUMBER_AGENTS;
    agentPool->next = 0;
}

// A function that returns a pointer to next agent in pool
Agent* newAgent(AgentPool* agentPool)
{
    size_t next = agentPool->next;
    if (next < MAX_NUMBER_AGENTS) {
        agentPool->next = next+1;
        return &agentPool->pool[next];
    }
    return NULL;
}

// A function to read a file with agent data in it, adding the agent to a agentlist and returning a reference to the agent
Agent* readAgent(FILE* file, AgentPool* agentPool)
{
    char line[MAX_LINE_LENGTH];
    int successAgentName = 0;
    int successAgentKey = 0;
    Agent* agent = newAgent(agentPool);

    if (fgets(line, MAX_LINE_LENGTH, file) && agent) {
        size_t i;
        for (i = 0; i < strlen(line) && line[i] != ',' && i < MAX_AGENTNAME_LENGTH-1; i++) {
            agent->name[i] = line[i];
        }
        agent->name[i] = '\0';
        while (i < strlen(line) && line[i] != ',') {
            i++;
        }
        if (line[i] == ',' && strlen(agent->name) > 0) {
            i++;
            successAgentName = 1;
            successAgentKey = sscanf(line+i, "%zu", &agent->key) == 1;
        }
    }
    if (agent && !(successAgentName && successAgentKey)) {
        deleteAgent(agent, agentPool);
        agent = NULL;
    }
    return agent;
}

// A function to delete an agent from an AgentPool
void deleteAgent(Agent* agent, AgentPool* agentPool)
{
    int i;
    int move = 0;
    for (i = 0; i < agentPool->next-1; i++) {
        if (move || &agentPool->pool[i] == agent) {
            move = 1;
            agentPool->pool[i] = agentPool->pool[i+1];
        }
    }

    agentPool->next--;
}

// A function that searches all agents for one with name
Agent* findAgent(char name[], AgentPool* agentPool)
{
    Agent* agent = NULL;
    for (int i = 0; i < agentPool->next; i++) {
        agent = &agentPool->pool[i];
        if (strcmp(name, agent->name) == 0) {
            return agent;
        }
    }
    return NULL;
}

void readAgentName(char agentName[], size_t maxAgentNameLength)
{
    char c;
    size_t i;

    c = getchar();
    for (i = 0; i < maxAgentNameLength-1 && c != '\n'; i++) {
        agentName[i] = c;
        c = getchar();
    }
    agentName[i] = '\0';
}
