#ifndef COM_ITERATOR_H
#define COM_ITERATOR_H

#include <stdbool.h>

#define iterator_next(it, e)       fiterator_next(it, (void**) e)
#define iterator_range_next(it, e) fiterator_range_next(it, (void**) e)

/**
 * @brief Iterator for loop condition and element retrieval.
 */
/**
 * @brief Holds state to your iterator.
 */
/**
 * @brief Holds state to your range iterator.
 */
typedef bool (*iterator_fn)(void* self, void** w);

typedef struct {
    void*       self;
    iterator_fn next;
} iterator_t;

typedef struct {
    void*       cursor;
    const void* endpos;
    size_t      step;
} iterator_range_t;

// Begin inline function definition.

/**
 * @brief Holds state to your iterator.
 */
inline bool fiterator_next(iterator_t* it, void** w)
{
    return it->next(it->self, w);
}

/**
 * @brief Holds state to your iterator.
 */
inline bool fiterator_range_next(iterator_range_t* it, void** w)
{
    *w         = it->cursor;
    it->cursor = (char*) it->cursor + it->step;
    return it->cursor <= it->endpos;
}

/**
 * @brief Holds state to your iterator.
 */
inline iterator_t make_iterator_range(iterator_range_t* it)
{
    return (iterator_t) {
        .self = (void*) it,
        .next = (iterator_fn) fiterator_range_next,
    };
}

// End inline function definition.

#endif // COM_ITERATOR_H