#include "../data/interpreter.h"
#include "../data/parser_datas/AST_node.h"
#include "./utils/hashmap.c"

static const char *ASTTypeName(ASTNodeType type)
{
	switch (type) {
		case AST_VARIABLE:
			return "VARIABLE";
		case AST_FUNCTION:
			return "FUNCTION";
		case AST_BINARY:
			return "BINARY";
		case AST_CALL:
			return "CALL";
		case AST_LITERAL:
			return "LITERAL";
		default:
			return "UNKNOWN";
	}
}

static void PrintASTBeingInterpreted(ASTNode *node, int index)
{
	printf("\n[Interpreter] AST #%d: %s\n", index, ASTTypeName(node->type));

	switch (node->type) {
		case AST_VARIABLE:
			printf("  identifier: %s\n", node->variable.identifier);
			printf("  type: %s\n", TokenTypeName(node->variable.varType));

			if (node->variable.varType == TYPE_TEXT) {
				printf("  value: %s\n", node->variable.value.text);
			} else {
				printf("  value: %d\n", node->variable.value.intValue);
			}
			break;

		case AST_FUNCTION:
			printf("  name: %s\n", node->function.name);
			break;

		case AST_CALL:
			printf("  name: %s\n", node->call.name);
			break;

		case AST_BINARY:
			printf("  operator: %s\n", TokenTypeName(node->binary.operator));
			break;

		case AST_LITERAL:
			printf("  type: %s\n", TokenTypeName(node->literal.type));
			break;

		default:
			break;
	}
}

void Interpreter(ASTList *headList){
	ASTList *current = headList;
	HashMap *variablesMap = HashMapInit();
	
	int index = 0;

	printf("\n========== INTERPRETER ==========");

	while (current != NULL) {
		if (current->current != NULL) {
			PrintASTBeingInterpreted(current->current, index);
			index++;
		}

		current = current->next;
	}

	if (index == 0) {
		printf("\nNenhuma AST para interpretar.\n");
	}

	printf("\n=================================\n");
}

int CheckAST(ASTNode *current, HashMap *variablesMap){
	if(current->type == AST_VARIABLE){
		//tratar para valores em asts binarios e reduzir para apenas um 
				
		HashMapAdd(variablesMap, current);
	}
	else if(current->type == AST_CALL){
		
	}

}