import bisect

MAX_X = 10**5
MAX_Y = 500

points = [] # List of all the points

# Since MAX_Y is relatively small
# For every Y coordinate we create a list of corresponding X coordinates.
# We could have used a dict/map, but then the lookup time will increse from O(1) to O(log n)
points_y = [
    [] for _ in range(MAX_Y + 1)
]

N = int(input())
for _ in range(N):
    X, Y = map(int, input().split())
    points.append((X, Y)) # Add the point to the list of points
    points_y[Y].append(X) # Add the X coordinate to the corresponding list of X values

# We push the extreme points also the list of points.
points.append((0, 0))
points.append((MAX_X, 0))

# Add the X coordinate of the extreme points to the corresponding Y value which here is 0
points_y[0].append(0)
points_y[0].append(MAX_X)

# Sort all the points.
points.sort()

# Sort all the points in the points_y array also
for i in range(MAX_Y + 1):
    points_y[i].sort()

# To calculate the answer, we go through each of the points
# Each point has 2 possibilities:
# Case-1: Can be a point on the right side of the rectangle
# Case-2: Can be a point on the top side of the rectangle
answer = 0
for i in range(1, len(points)):
    x, y = points[i]
    # Case-1
    # We calculate the strip area between this point and the previous point
    prev_x, prev_y = points[i - 1]
    area = MAX_Y * (x - prev_x)
    answer = max(answer, area)
    # Case-2
    # We find two points with Y coordinate lesser than the current Y coordinate
    # One point with X coordinate lesser and one with X coordinate greater than the current X coordinate
    if area > 0:
        x_left = 0
        x_right = MAX_X
        found_left = False
        found_right = False
        for j in range(y - 1, -1, -1):
            # Check if the particular Y coordinate has any points or not.
            if len(points_y[j]) > 0:
                # Get the largest value of X coordinate closest to the current X coordinate, left of the current X coordinate
                x_left_index = bisect.bisect_left(points_y[j], x) - 1
                if x_left_index > -1:
                    x_left = max(x_left, points_y[j][x_left_index])
                # Get the smallest value of X coordinate closest to the current X coordinate, right of the current X coordinate
                x_right_index = bisect.bisect_right(points_y[j], x)
                if x_right_index < len(points_y[j]):
                    x_right = min(x_right, points_y[j][x_right_index])
                if x_left_index == x - 1:
                    found_left = True
                if x_right_index == x + 1:
                    found_right = True
                if found_left and found_right:
                    break

        area = y * (x_right - x_left)
        answer = max(answer, area)
print(answer)
