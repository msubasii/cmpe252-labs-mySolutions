#include <stdio.h>
#include <math.h>
#include <string.h>

#include <ctype.h> // Include the ctype.h header for the toupper() function

#define MAX_SHAPES 50

/* type definitions */
typedef struct {
    double x;
    double y;
    double z;
} point_t;

typedef struct {
    point_t center;
    double radius;
} sphere_t;

typedef struct {
    point_t center;
    double side;
} cube_t;

typedef struct {
    point_t center;
    double base_side;
    double height;
} square_prism_t;

typedef union {
    cube_t cube;
    square_prism_t square_prism;
    sphere_t sphere;
} shape3d_data_t;

typedef enum {
    CUBE,
    SQUARE_PRISM,
    SPHERE
} class_t;

typedef struct {
    class_t type;
    shape3d_data_t shape;
} shape_t;

/* function prototypes */
int scanShape(FILE *filep, shape_t *objp);
int loadShapes(shape_t shapes[]);
void printShape(const shape_t *objp);

int main()
{
    shape_t shapes[MAX_SHAPES];
    int numOfShapes = loadShapes(shapes);

    printf("\nShapes 3D:\n");
    for (int i = 0; i < numOfShapes; i++)
        printShape(&shapes[i]);

    return 0;
}

// Scans a shape from a file and fills the shape_t object
int scanShape(FILE *filep, shape_t *objp)
{
    char shapeType[20];
    int readCount = fscanf(filep, "%s", shapeType);

    if (readCount == EOF)
        return 0;

    // Determine the shape type based on the scanned string
    if (strcmp(shapeType, "cube") == 0) {
        objp->type = CUBE;
        readCount = fscanf(filep, "%lf %lf %lf %lf",
                           &objp->shape.cube.center.x,
                           &objp->shape.cube.center.y,
                           &objp->shape.cube.center.z,
                           &objp->shape.cube.side);
    } else if (strcmp(shapeType, "square_prism") == 0) {
        objp->type = SQUARE_PRISM;
        readCount = fscanf(filep, "%lf %lf %lf %lf %lf",
                           &objp->shape.square_prism.center.x,
                           &objp->shape.square_prism.center.y,
                           &objp->shape.square_prism.center.z,
                           &objp->shape.square_prism.base_side,
                           &objp->shape.square_prism.height);
    } else if (strcmp(shapeType, "sphere") == 0) {
        objp->type = SPHERE;
        readCount = fscanf(filep, "%lf %lf %lf %lf",
                           &objp->shape.sphere.center.x,
                           &objp->shape.sphere.center.y,
                           &objp->shape.sphere.center.z,
                           &objp->shape.sphere.radius);
    }

    // Skip the newline character after reading the shape type
    int c;
    while ((c = fgetc(filep)) != '\n' && c != EOF)
        ;

    if (readCount == 4 || readCount == 5)
        return 1;
    else
        return 0;
}

// Loads shapes from a file and returns the number of read shapes
int loadShapes(shape_t shapes[])
{
    char fileName[50];
    FILE *filep;
    int shapeCount = 0;

    printf("Enter the file name to read: ");
    scanf(" %s", fileName); // Include whitespace before %s

    filep = fopen(fileName, "r");
    if (filep == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    printf("Opening %s\n", fileName);

    // Read shapes from the file until the maximum number of shapes is reached or end of file is reached
    while (shapeCount < MAX_SHAPES && scanShape(filep, &shapes[shapeCount]))
        shapeCount++;

    printf("Loading complete\n");
    fclose(filep);
    printf("Closing %s\n", fileName);

    return shapeCount;
}

// Prints the details of a shape object
void printShape(const shape_t *objp)
{
    switch (objp->type) {
        case CUBE:
            printf("Cube: <%.2lf %.2lf %.2lf> <%.2lf>\n",
                   objp->shape.cube.center.x,
                   objp->shape.cube.center.y,
                   objp->shape.cube.center.z,
                   objp->shape.cube.side);
            break;
        case SQUARE_PRISM:
            printf("Square_prism: <%.2lf %.2lf %.2lf> <%.2lf %.2lf>\n",
                   objp->shape.square_prism.center.x,
                   objp->shape.square_prism.center.y,
                   objp->shape.square_prism.center.z,
                   objp->shape.square_prism.base_side,
                   objp->shape.square_prism.height);
            break;
        case SPHERE:
            printf("Sphere: <%.2lf %.2lf %.2lf> <%.2lf>\n",
                   objp->shape.sphere.center.x,
                   objp->shape.sphere.center.y,
                   objp->shape.sphere.center.z,
                   objp->shape.sphere.radius);
            break;
    }
}
