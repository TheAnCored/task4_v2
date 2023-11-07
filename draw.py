import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Define the eight vertices of the cube
vertices = [

 ( -10.0000, -10.0000, -10.0000 ),
 ( 10.0000, -10.0000, -10.0000 ),
 ( -10.0000, 10.0000, -10.0000 ),
 ( -10.0000, -10.0000, 10.0000 ),
 ( -10.0000, 10.0000, 10.0000 ),
 ( 10.0000, -10.0000, 10.0000 ),
 ( 10.0000, 10.0000, -10.0000 ),
 ( 10.0000, 10.0000, 10.0000 ),


]


# Plot the vertices
for vertex in vertices:
    ax.scatter(*vertex)

# Plot the edges
for vertice in vertices:
    ax.plot([vertices[0][0], vertices[0][0]],
            [vertices[1][1], vertices[1][1]],
            [vertices[2][2], vertices[2][2]])

# Set the axis labels
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Set the plot title
ax.set_title('Cube')

# Display the plot
plt.show()
