triangle:
	@echo "Generating executable..."
	@gcc triangle.c -o executable -lm
	@echo "Done"

clean:
	@echo "Cleaning up..."
	@rm -rf .points .vertices executable
	@echo "Done"
