/*
 * This program will allocate some big amount of RAM,
 * then will wait for a while before freeing almost all.
 * After that will wait for a while again before finishing.
 * Could be used for testing how OS manage memory per process.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define RAM_TO_BE_ALLOCATED (1*1024*1024*1024lu)
#define CHUNK_SIZE (1024lu)/*[bytes]*/
#define TIME_TO_WAIT_IN_FULL_ALLOCATION (30lu) /*[s]*/
#define RAM_TO_BE_FREED ((RAM_TO_BE_ALLOCATED) - (50*1024*1024lu))
#define TIME_TO_WAIT_IN_LOW_ALLOCATION (60lu) /*[s]*/

typedef struct SList TList;

struct SList
{
	TList* next;
	char* data;
};

void allocate_ram(TList** head, const size_t how_much_ram,
		const size_t size_fo_chunk, const size_t wait_between_operations_uS);

void deallocate_ram(TList** head, const size_t how_much_ram,
		const size_t size_fo_chunk, const size_t wait_between_opeartions_uS);

void deallocate_all(TList** head);

/*----------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
	TList *head = 0;

	printf("\nargc = %d\targv[0] = %s\n", argc, argv[0]);

	allocate_ram(&head, RAM_TO_BE_ALLOCATED, CHUNK_SIZE, 1);

	printf("Going to sleep for %lu seconds...\n",
			TIME_TO_WAIT_IN_FULL_ALLOCATION);

	sleep(TIME_TO_WAIT_IN_FULL_ALLOCATION);

	deallocate_ram(&head, RAM_TO_BE_FREED, CHUNK_SIZE, 1);

	printf("RAM in use now is %lu bytes! Going to sleep for %lu seconds!\n",
			RAM_TO_BE_ALLOCATED-RAM_TO_BE_FREED,
			TIME_TO_WAIT_IN_LOW_ALLOCATION);

	 sleep(TIME_TO_WAIT_IN_LOW_ALLOCATION);

	deallocate_all(&head);

	printf("GOOD BYE!\n");
	return 0;
}

/*----------------------------------------------------------------------------*/

void allocate_ram(TList** head, const size_t how_much_ram,
		const size_t size_fo_chunk, const size_t wait_between_operations_uS)
{
	size_t allocated = 0;
	TList* temp = 0;
	size_t counter = 0;

	printf("Going to allocate %lu bytes of RAM in chunks of %lu!\n",
			how_much_ram, size_fo_chunk);

	while(allocated < how_much_ram)
	{
		temp = *head;
		*head = (TList*)malloc(sizeof(TList));
		(*head)->data = malloc(size_fo_chunk);
		(*head)->next = temp;
		counter++;
		allocated += size_fo_chunk;
		usleep(wait_between_operations_uS);
	}

	printf("Allocated %lu elements each of %lu bytes!\n",
			counter+1, size_fo_chunk);
}

/*----------------------------------------------------------------------------*/

void deallocate_ram(TList** head, const size_t how_much_ram,
		const size_t size_fo_chunk, const size_t wait_between_opeartions_uS)
{
	size_t deallocated = 0;
	TList* temp = 0;
	size_t counter = 0;

	printf("Going to free %lu bytes!\n", how_much_ram);

	while((deallocated < how_much_ram) && (head != 0))
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->data);
		free(temp);
		deallocated += size_fo_chunk;
		counter++;
		usleep(wait_between_opeartions_uS);
	}

	printf("Freed %lu elements each %lu bytes!\n", counter, size_fo_chunk);
}

/*----------------------------------------------------------------------------*/

void deallocate_all(TList** head)
{
	TList* temp = 0;

	while(*head != 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->data);
		free(temp);
	}
}
