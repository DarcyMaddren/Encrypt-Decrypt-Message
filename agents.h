/*
 * Declare the Agent Type, Agent Pool and operations on it.
 *
 * Author: Darcy Maddren
 * Date: September 2020
 */

#ifndef AGENT_H
#define AGENT_H

/* Agent Structure, used to hold their name and
   a key used for encryption and decryption. */
typedef struct {
    char name[MAX_AGENTNAME_LENGTH];
    size_t key;
} Agent;

/* Agent Pool Structure, used to hold a list of all
   agents, with pointers to the size of the pool and
   the next open agent slot. */
typedef struct {
    size_t size;
    size_t next;
    Agent  pool[MAX_NUMBER_AGENTS];
} AgentPool;

/* */
void encryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength);

/* */
void decryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength);

/* */
size_t readText(FILE* file, char text[], size_t maxTextSize);

/* */
size_t readCipherBook(FILE* file, char text[], size_t maxTextSize);

/* */
size_t readMessage(FILE* file, char text[], size_t maxTextSize);

/* */
void initAgentPool(AgentPool* agentPool);

/* */
Agent* newAgent(AgentPool* agentPool);

/* */
void deleteAgent(Agent* agent, AgentPool* agentPool);

/* */
Agent* readAgent(FILE* file, AgentPool* agentPool);

/* */
Agent* findAgent(char name[], AgentPool* agentPool);

/* */
void readAgentName(char agentName[], size_t maxAgentNameLength);
