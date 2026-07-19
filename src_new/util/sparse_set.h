#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * @param SPARSE_SET_OK            Success.
 * @param SPARSE_SET_ERR_NULL      Set provided is NULL.
 * @param SPARSE_SET_ERR_BOUNDS    Sparse ID provided is less than 0 or sparse_max.
 * @param SPARSE_SET_ERR_EXISTS    Attempting to add an entry for an ID which is already in the set.
 * @param SPARSE_SET_ERR_FULL      Dense is full, set cannot fit more entries.
 * @param SPARSE_SET_ERR_NOT_FOUND No entry found for given sparse ID.
 */
typedef enum {
    SPARSE_SET_OK            = 0,
    SPARSE_SET_ERR_NULL      = 1,
    SPARSE_SET_ERR_BOUNDS    = 2,
    SPARSE_SET_ERR_EXISTS    = 3,
    SPARSE_SET_ERR_FULL      = 4,
    SPARSE_SET_ERR_NOT_FOUND = 5,
} sparse_set_err;

/**
 * @param sparse      Sparce array where index = sparse ID, the location at each ID contains 
 *                    the index of the ID's entry in dense, or -1 if not in set.
 * @param sparse_max  Total amount of ID's that could potentially be in this set (the ID space).
 * @param dense       Tightly packed array of all set entries
 * @param dense_max   Maximum number of entries that can be in this set.
 * @param dense_ids   Reverse index of sparse, dense index -> sparse ID
 * @param entry_size   Size in bytes of each entry in dense.
 * @param tail        Index of the last entry in dense.
 */
typedef struct {
    int     *sparse;
    int      sparse_max;
    uint8_t *dense;
    int      dense_max;
    int     *dense_ids;
    int      entry_size;
    int      tail;
} sparse_set;

/**
 * @brief Creates a sparse set.
 *
 * @param sparse_max The total amount of entries that could potentially be in this set (the ID space).
 * @param dense_max  The maximum number of entries that can be in this set.
 * @param entry_size  The size in bytes of each entry in dense.
 *
 * @return A sparse_set initialized with the given parameters, or NULL if memory alocation fails
 */
sparse_set *sparse_set_create(int sparse_max, int dense_max, int entry_size) {
    sparse_set *set = malloc(sizeof(sparse_set));
    if (!set) return NULL;
    
    // initialise and alocate memory
    *set = (sparse_set) {
        .sparse      = malloc(sparse_max * sizeof(int)),
        .sparse_max  = sparse_max,
        .dense       = malloc(dense_max * entry_size),
        .dense_max   = dense_max,
        .dense_ids   = malloc(dense_max * sizeof(int)),
        .entry_size   = entry_size,
        .tail        = 0
    };

    // if anything failed free resources and return NULL
    if (!set->sparse || !set->dense || !set->dense_ids) {
        free(set->sparse);
        free(set->dense);
        free(set->dense_ids);
        free(set);
        return NULL;
    }

    // initialise sparse to -1's meaning no entrys are in the set
    memset(set->sparse, -1, sparse_max * sizeof(int));
    
    return set;
}

/**
 * @brief Destroy and free resources for a sparse_set.
 * 
 * @param set sparse_set to destroy
 */
void sparse_set_destroy(sparse_set *set) {
    if (!set) return;
    free(set->sparse);
    free(set->dense);
    free(set->dense_ids);
    free(set);
}

/**
 * @brief Add an entry to an ID.
 *
 * @param set   sparse_set to add entry to.
 * @param id    ID to assign entry to.
 * @param data  Entry data. Should be of set.entry_size
 *
 * @return A sparse_set_err indicating the result.
 */
sparse_set_err sparse_set_add(sparse_set *set, int id, void *data) {
    if (!set)                            return SPARSE_SET_ERR_NULL;
    if (!data)                           return SPARSE_SET_ERR_NULL;
    if (id < 0 || id >= set->sparse_max) return SPARSE_SET_ERR_BOUNDS;
    if (set->sparse[id] != -1)           return SPARSE_SET_ERR_EXISTS;
    if (set->tail >= set->dense_max)     return SPARSE_SET_ERR_FULL;

    int tail_index = set->tail;

    set->dense_ids[tail_index] = id;         // ID gets tail index
    set->sparse[id]            = tail_index; // ID gets tail index

    uint8_t *destination = set->dense + (set->tail * set->entry_size); // calculate tail address

    memcpy(destination, data, set->entry_size); // store IDs data at tail

    set->tail++;
    return SPARSE_SET_OK;
}

/**
 * @brief Remove an entry from an ID.
 *
 * @param set  sparse_set to remove entry from.
 * @param id   ID to remove entry from.
 *
 * @return A sparse_set_err indicating the result.
 */
sparse_set_err sparse_set_remove(sparse_set *set, int id) {
    if (!set)                            return SPARSE_SET_ERR_NULL;
    if (id < 0 || id >= set->sparse_max) return SPARSE_SET_ERR_BOUNDS;
    int index = set->sparse[id];
    if (index == -1)                     return SPARSE_SET_ERR_NOT_FOUND;

    int last_index = set->tail - 1;
    int last_id    = set->dense_ids[last_index];

    uint8_t *hole = set->dense + (index * set->entry_size);     // Item to remove  
    uint8_t *plug = set->dense + (last_index * set->entry_size); // Last entry, to replace the removed one

    memcpy(hole, plug, set->entry_size); // Copy plug data overtop of hole's.
    set->sparse[last_id]  = index;      // Set index to the now filled holes


    set->dense_ids[index] = last_id;  
    set->sparse[id] = -1;
    set->tail--;
    return SPARSE_SET_OK;
}

/**
 * @brief Get entry assigned to ID
 *
 * @param set  sparse_set to get entry from.
 * @param id   ID to get entry from.
 *
 * @return void * to entry, of size sparse_set.entry_size. Or NULL if not present or parameters invalid
 */
void *sparse_set_get(sparse_set *set, int id) {
    if (!set)                            return NULL;
    if (id < 0 || id >= set->sparse_max) return NULL;
    int index = set->sparse[id];
    if (index == -1)                     return NULL;

    return set->dense + (index * set->entry_size);
}

/**
 * @brief Check if set has an entry assigned to ID
 *
 * @param set  sparse_set to check ID from.
 * @param id   ID to check.
 *
 * @return 1 if present 0 if not, or 0 on error.
 */
char sparse_set_has(sparse_set *set, int id) {
    if (!set) return 0;
    if (id < 0 || id >= set->sparse_max) return 0;

    return set->sparse[id] != -1;
}