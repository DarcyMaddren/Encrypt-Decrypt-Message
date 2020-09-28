/*
 * Declare the Agent Type, Agent Pool and operations on it.
 *
 * Author: Darcy Maddren
 * Date: September 2020
 */

#ifndef AGENT_H
#define AGENT_H

/* Common Declerations. */
#define MAX_NUMBER_AGENTS         15
#define MAX_AGENTNAME_LENGTH      45

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

/* Encrypts a given message, using a shift key created with
   the current agent key plus the char in the encryption book,
   at the current index. */
void encryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength);

/* Decrypts a given encrypted message, with an inverse of the
   encrypt key. (Current book char at the index and agent key) */
void decryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength);

/* Reads characters in a given text file as intagers and places
   them in an array of characters of maxTextSize. Returns the
   final count of character in that array. */
size_t readText(FILE* file, char text[], size_t maxTextSize);

/* Uses readText to read the contents of the given cipeher file,
   then loops through removing all white space characters into
   a buffer of characters. Returns the final size of that buffer. */
size_t readCipherBook(FILE* file, char text[], size_t maxTextSize);

/* Uses readText to read the contents of the given message file,
   then loops through replacing '\n' and '\t' with corresponding
   intagers. As well as shifting each character back by 31 and
   placing all of this into a char buffer. Returns the size of
   the outpute buffer. */
size_t readMessage(FILE* file, char text[], size_t maxTextSize);

/* Initializes the agent pool, setting the size to a pre defined
   max size and next index pointer to 0. */
void initAgentPool(AgentPool* agentPool);

/* Checks if there is enough space in the agent pool for a new
   agent and returns a pointer to that space if there is, else
   a null value will be returned. */
Agent* newAgent(AgentPool* agentPool);

/* Reads a line from an input agent file containing agent info
   and adds that agent to the agent pool if there is space and
   it is a valid line. The function returns a pointer to that
   agent if added. */
Agent* readAgent(FILE* file, AgentPool* agentPool);

/* Removes a specified agent from the agent pool and decrements
   next agent. */
void deleteAgent(Agent* agent, AgentPool* agentPool);

/* Searches the agent pool for an array of characters. Returns
   a pointer to that agent if it is found. (otherwise NULL) */
Agent* findAgent(char name[], AgentPool* agentPool);

/* Reads a string of characters specified by the user (input)
   and adds them to an agentName array. */
void readAgentName(char agentName[], size_t maxAgentNameLength);

#endif
