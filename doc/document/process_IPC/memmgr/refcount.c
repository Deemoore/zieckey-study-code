/* Structure Definitions*/
/* Base structure that holds a refcount */
struct refcountedstruct
{
	int refcount;
}
/* All refcounted structures must mirror struct
* refcountedstruct for their first variables
*/
/* Refcount maintenance functions */
/* Increase reference count */
void REF(void *data)
{
	struct refcountedstruct *rstruct;
	rstruct = (struct refcountedstruct *) data;
	rstruct->refcount++;
}
/* Decrease reference count */
void UNREF(void *data)
{
	struct refcountedstruct *rstruct;
	rstruct = (struct refcountedstruct *) data;
	rstruct->refcount--;
	/* Free the structure if there are no more users */
	if(rstruct->refcount == 0)
	{
		free(rstruct);
	}
}


\








/* EXAMPLES OF USAGE */
/* Data type to be refcounted */
struct mydata
{
	int refcount; /* same as refcountedstruct */
	int datafield1; /* Fields specific to this struct */
	int datafield2;
	/* other declarations would go here as appropriate */
};
/* Use the functions in code */
void dosomething(struct mydata *data)
{
	REF(data);
	/* Process data */
	/* when we are through */
	UNREF(data);
}
struct mydata *globalvar1;
/* Note that in this one, we don't decrease the
* refcount since we are maintaining the reference
* past the end of the function call through the
* global variable
*/
void storesomething(struct mydata *data)
{
	REF(data); /* passed as a parameter */
	globalvar1 = data;
	REF(data); /* ref because of Assignment */
	UNREF(data); /* Function finished */
}



