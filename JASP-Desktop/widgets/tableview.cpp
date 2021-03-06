
#include "tableview.h"

#include <QHeaderView>
#include <QResizeEvent>

#include "draganddrop.h"

#include <QDebug>
#include <QMouseEvent>

#include "widgets/tableviewmenueditordelegate.h"

TableView::TableView(QWidget *parent) :
	QTableView(parent)
{
	_tableModel = NULL;
	_defaultDropTarget = NULL;

	connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickedHandler(QModelIndex)));

	horizontalHeader()->hide();
	verticalHeader()->hide();
	verticalHeader()->setDefaultSectionSize(verticalHeader()->fontMetrics().height() + 2);

	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setItemDelegate(new TableViewMenuEditorDelegate(this));
}

void TableView::setModel(QAbstractItemModel *model)
{
	_tableModel = qobject_cast<TableModel *>(model);

	QTableView::setModel(model);
}

void TableView::setDoubleClickTarget(DropTarget *target)
{
	_defaultDropTarget = target;
}

void TableView::notifyDragWasDropped()
{
	if (_tableModel != NULL)
		_tableModel->mimeDataMoved(selectedIndexes());
}

void TableView::focusInEvent(QFocusEvent *event)
{
	QTableView::focusInEvent(event);
	focused();
}

void TableView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	QTableView::selectionChanged(selected, deselected);
	selectionUpdated();
}

void TableView::dropEvent(QDropEvent *event)
{
	QTableView::dropEvent(event);

	if (event->isAccepted() && event->dropAction() == Qt::MoveAction)
	{
		QObject *source = event->source();
		DropTarget *draggedFrom = dynamic_cast<DropTarget*>(source);
		if (draggedFrom != NULL)
			draggedFrom->notifyDragWasDropped();
	}
}

void TableView::mousePressEvent(QMouseEvent *event)
{
	QModelIndex index = indexAt(event->pos());

	if (index.flags() & Qt::ItemIsEditable)
		edit(index);
	else
		QTableView::mousePressEvent(event);
}

void TableView::resizeEvent(QResizeEvent *event)
{
	QTableView::resizeEvent(event);

	int columnCount = model()->columnCount();

	if (columnCount > 1)
	{
		int overallWidth = event->size().width();

		QList<int> widths;
		int sum = 0;

		for (int i = 0; i < columnCount; i++)
		{
			int width = 0;

			QVariant v = this->model()->headerData(i, Qt::Horizontal, Qt::SizeHintRole);

			if (v.canConvert(QMetaType::QSize))
				width = v.toSize().width();
			if (width <= 0)
				width = this->horizontalHeader()->defaultSectionSize();

			sum += width;
			widths.append(width);
		}

		double multiplier = (double)overallWidth / sum;

		for (int i = 0; i < columnCount; i++)
		{
			double width = widths.at(i) * multiplier;
			setColumnWidth(i, width);
		}
	}
}

void TableView::doubleClickedHandler(const QModelIndex index)
{
	Q_UNUSED(index);

	if (_defaultDropTarget != NULL)
		DragAndDrop::perform(this, _defaultDropTarget);
}
