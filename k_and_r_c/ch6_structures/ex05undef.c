// implement symbol table lookup

struct nlist {
    struct nlist* next;
    char *name;
    char *defn;
};
#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *s)
{
    unsigned hashval;
    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist* ptr;
    for(ptr = hashtab[hash(s)]; ptr != NULL; ptr = ptr->next)
        if(strcmp(ptr->name, s) == 0)
            return ptr;
    return NULL;
}

struct nlist *install(char *s, char *d)
{
    struct nlist *np;

    if((np = lookup(s)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if(np == NULL || (np->name = strdup(s)) == NULL)
            return NULL; 
        np->next = hashtab[hash(s)]
        hashtab[hash(s)] = np;
    } else
        free((void *)np->defn);
    if((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *s)
{
    struct nlist *np, *ptr;
    if((np = lookup(s)) != NULL){
        ptr = hashtab[hash(s)];
        if (ptr == np)
            hashtab[hash(s)] = np->next;
        else {
            for(; ptr->next != np; ptr = ptr->next)
                ;
            ptr->next = np->next;
        }
        free(np);
        return ptr;
    }
}
