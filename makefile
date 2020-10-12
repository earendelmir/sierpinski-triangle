triangle triangle.c:
	@echo "Generating executable \"sierpinski-triangle\""
	@gcc triangle.c -o sierpinski-triangle -lm
	@echo "Done."

clean:
	@echo "Cleaning up..."
	@rm -rf .points .vertices sierpinski-triangle
	@echo "Done"
