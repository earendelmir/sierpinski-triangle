SOURCES=src/sources

triangle:
	@echo "Generating executable..."
	@gcc triangle.c -o triangle -lm
	@echo "Done"

clean:
	@echo "Cleaning up..."
	@rm -rf .vscode/ libraries/ triangle
	@echo "Done"

