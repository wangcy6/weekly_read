### 程序的入口:func (e *DDLExec) Next





### 创建表：func (d *ddl) CreateTable





### 数据结果

~~~golang
// ExecStmt implements the sqlexec.Statement interface, it builds a planner.Plan to an sqlexec.Statement.
type ExecStmt struct {
	// GoCtx stores parent go context.Context for a stmt.
	GoCtx context.Context
	// InfoSchema stores a reference to the schema information.
	InfoSchema infoschema.InfoSchema
~~~

