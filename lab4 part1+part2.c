#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_SHAPES 50

typedef struct {
    double x;
    double y;
} point_t;

typedef struct {
    point_t bottom_left;
    point_t bottom_right;
    point_t upper_left;
    point_t upper_right;
    double side;
} square_t;

int scanShape(FILE *filep, square_t *objp);
int loadShapes(square_t shapes[]);
void printShape(const square_t *objp);
void centerDistance(const point_t *ptp, const square_t *objp);

int scanShape(FILE *filep, square_t *objp) {
    char shapeType[10];
    double cx, cy, side;
    int result = fscanf(filep, "%s %lf %lf %lf", shapeType, &cx, &cy, &side);
    if (result == 4) {
        if (strcmp(shapeType, "square") == 0) {
            objp->bottom_left.x = cx - side / 2.0;
            objp->bottom_left.y = cy - side / 2.0;
            objp->bottom_right.x = cx + side / 2.0;
            objp->bottom_right.y = cy - side / 2.0;
            objp->upper_left.x = cx - side / 2.0;
            objp->upper_left.y = cy + side / 2.0;
            objp->upper_right.x = cx + side / 2.0;
            objp->upper_right.y = cy + side / 2.0;
            objp->side = side;
            return 1;
        }
    }
    return 0;
}

int loadShapes(square_t shapes[]) {
    char filename[100];
    printf("Enter the file name to read: ");
    scanf("%s", filename);

    FILE *filep = fopen(filename, "r");
    if (filep == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }

    printf("Opening %s\n", filename);

    int numOfShapes = 0;
    while (numOfShapes < MAX_SHAPES) {
        int result = scanShape(filep, &shapes[numOfShapes]);
        if (result == 0)
            break;
        numOfShapes++;
    }

    printf("Loading complete\n");

    fclose(filep);
    printf("Closing %s\n", filename);

    return numOfShapes;
}

void printShape(const square_t *objp) {
    static int squareNumber = 0;
    printf("Square %d: <", squareNumber);
    printf("%.2lf %.2lf> ", objp->bottom_left.x, objp->bottom_left.y);
    printf("<%.2lf %.2lf> ", objp->bottom_right.x, objp->bottom_right.y);
    printf("<%.2lf %.2lf> ", objp->upper_left.x, objp->upper_left.y);
    printf("<%.2lf %.2lf> ", objp->upper_right.x, objp->upper_right.y);
    printf("<%.2lf>\n", objp->side);
    squareNumber++;
}
void centerDistance(const point_t *ptp, const square_t *objp) {
    double cx = (objp->bottom_left.x + objp->bottom_right.x) / 2.0;
    double cy = (objp->bottom_left.y + objp->upper_left.y) / 2.0;
    double distance = sqrt(pow((ptp->x - cx), 2) + pow((ptp->y - cy), 2));
    printf("%.2lf", distance);
}


int main() {
    square_t shapes[MAX_SHAPES];
    int numOfShapes = loadShapes(shapes);

    printf("\nSquares:\n");
    for (int i = 0; i < numOfShapes; i++) {
        printShape(&shapes[i]);
    }

    printf("Enter x and y coordinate of the point: ");
    point_t userPoint;
    scanf("%lf %lf", &userPoint.x, &userPoint.y);

    printf("\nCenter distances are:\n");
    for (int i = 0; i < numOfShapes; i++) {
        printf("Square %d: ", i + 1);
        centerDistance(&userPoint, &shapes[i]);
        printf("\n");
    }

    return 0;
}

