#ifndef OBB_H
#define OBB_H

#include "v.h"

// OBB: Oriented Bounding Box
typedef struct {
  V center;
  V half_extents;
  V axis[3]; // Local axes: typically the normalized right, up, and forward directions.
} OBB;

// Create a new OBB given its center, half extents, and orientation axes.
// The 'axes' array should contain 3 normalized vectors representing the local x, y, and z axes.
OBB OBB_new(V center, V half_extents, V axes[3]);

// Create a new symmetric OBB centered at the origin with given half extents and orientation axes.
OBB OBB_new_sym(V half_extents, V axes[3]);

// Translate the OBB by the vector 'v' (only the center moves; orientation remains unchanged).
OBB OBB_translate(OBB obb, V v);

 // Start Generation Here
// Rotate the OBB by a specified angle (in radians) around the given axis.
// The rotation is applied to both the center and the local axes of the OBB.
// Parameters:
//   obb   - The original oriented bounding box.
//   angle - The rotation angle in radians.
//   axis  - The normalized axis around which the OBB will be rotated.
// Returns a new OBB, rotated accordingly.
OBB OBB_rotate(OBB obb, float angle, V axis);

// Generate a string representation of the OBB.
// The returned string is dynamically allocated and should be freed after use.
const char* OBB_to_string(OBB obb);

// Check if two OBBs intersect (returns 1 if they intersect, 0 otherwise).
// Implementation typically uses the Separating Axis Theorem.
int OBB_intersects(OBB obb1, OBB obb2);

#endif // !OBB_H
