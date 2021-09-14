#include "io_gdata.h"

// Loads a GData from a file
// and resources inside it
bool LoadGDATA(GData *gdata, const char *filename)
{
    // A GData file consists of a header "GDATA" the number of resources and a list of resources

    // Open the file
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return false;
    }

    // Read the header
    char header[5];
    fread(header, 1, 4, fp);
    header[4] = '\0';
    if (strcmp(header, "GDATA") != 0)
    {
        printf("Error: File %s is not a GDATA file\n", filename);
        fclose(fp);
        return false;
    }

    // Read the number of resources
    unsigned int numResources;
    fread(&numResources, 1, 4, fp);

    // Create the GData
    gdata->size = numResources;
    gdata->resources = malloc(sizeof(GResource) * numResources);

    for (unsigned int i = 0; i < numResources; i++)
    {
        // Read a 32 byte char array
        char name[32];
        fread(name, 1, 32, fp);

        // Read the size in unsigned int of the GResource
        unsigned int size;
        fread(&size, 1, 4, fp);

        // Read the data
        char *data = malloc(size);
        fread(data, 1, size, fp);

        // Add the resource to the GData

        gdata->resources[i].size = size;
        gdata->resources[i].data = data;
        strcpy(gdata->resources[i].name, name);
    }

    // Close the file
    fclose(fp);
    return true;
}

// Free GData
// and all resources inside it
void FreeGDATA(GData *gdata)
{
    GResource *resources = gdata->resources;
    for (int i = 0; i < gdata->size; i++)
    {
        free(resources[i].data);
        free(&resources[i]);
    }
    free(gdata);
}

// Write data to GData
void WriteToGDATA(GData *gdata, const char *resourceName, int resourceSize, char *resourceData)
{
    GResource *resource = malloc(sizeof(GResource));
    resource->size = resourceSize;
    resource->data = resourceData;
    strcpy_s(resource->name, RES_MAX_STR, resourceName);

    // Reallocate the GData
    size_t newSize = gdata->size + 1;
    gdata->resources = realloc(gdata->resources, sizeof(GResource) * newSize);
    gdata->resources[gdata->size] = *resource;
    gdata->size++;
}

bool SaveGDATA(GData *gdata, const char *filename)
{
    // Open the file
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("Error: Could not write to file %s\n", filename);
        return false;
    }

    // Write the header "GDATA"
    fwrite("GDATA", 1, 4, fp);

    // Write the number of resources
    fwrite(&gdata->size, 1, 4, fp);

    // Write the resources
    for (int i = 0; i < gdata->size; i++)
    {
        // Write the name
        fwrite(gdata->resources[i].name, 1, 32, fp);

        // Write the size
        fwrite(&gdata->resources[i].size, 1, 4, fp);

        // Write the data
        fwrite(gdata->resources[i].data, 1, gdata->resources[i].size, fp);
    }

    // Close the file
    fclose(fp);
    return true;
}

GData *CreateGDATA()
{
    GData *gdata = malloc(sizeof(GData));
    gdata->size = 0;
    gdata->resources = NULL;
    return gdata;
}