open Belt;
open Survey;

let _ = [%bs.raw {|require('./index.css')|}];

let setValue = (questions: array(Question.t), value, id) =>
  questions->Array.map(q => q.id === id ? {...q, value} : q);

let remove = (questions: array(Question.t), id) =>
  questions->Array.keep(q => q.id !== id);

[@react.component]
let make = () => {
  let (questions: array(Question.t), setQuestions) =
    React.useState(() => [||]);
  let (name, setName) = React.useState(() => "");
  <Layout>
    <div
      className={
        TW.[
          FontSize(Text3xl),
          Position(Sticky),
          Placement(Top0),
          Display(Flex),
          AlignItems(ItemsCenter),
          ZIndex(Z50),
          Height(H16),
          Width(TW.W8_12),
        ]
        ->TW.make
      }>
      <Text className=TW.[FontSize(Text2xl), Margin(Mr4)]>
        {j|Nowa ankieta:|j}
      </Text>
      <Input
        value=name
        onChange={value => setName(_ => value)}
        className=TW.[Width(TW.W6_12), FontSize(Text2xl)]
        placeholder="Nazwa ankiety"
      />
    </div>
    <div className={[Height(H8)]->TW.make} />
    <Animation.Presence>
      {questions
       ->Array.mapWithIndex((index, q) =>
           <div>
             {switch (q.type_) {
              | Open =>
                <OpenQuestion
                  index
                  placeholder={q.placeholder}
                  key={q.id}
                  value={q.value}
                  onChange={v =>
                    setQuestions(questions => setValue(questions, v, q.id))
                  }
                  onDelete={() =>
                    setQuestions(questions => remove(questions, q.id))
                  }
                />

              | Rate(answers)
              | Closed(answers) =>
                <CloseQuestion
                  index
                  key={q.id}
                  placeholder={q.placeholder}
                  value={q.value}
                  onChange={v =>
                    setQuestions(questions => setValue(questions, v, q.id))
                  }
                  onDelete={() =>
                    setQuestions(questions => remove(questions, q.id))
                  }
                  onChangeAnswer={(answerId, v) =>
                    setQuestions(questions =>
                      Question.changeAnswer(
                        ~questions,
                        ~questionId=q.id,
                        ~answerId,
                        ~value=v,
                      )
                    )
                  }
                  onAddAnswer={() =>
                    setQuestions(questions =>
                      Question.addAnswer(questions, q.id)
                    )
                  }
                  onDeleteAnswer={answerId =>
                    setQuestions(questions =>
                      Question.removeAnswer(
                        ~answerId,
                        ~questionId=q.id,
                        questions,
                      )
                    )
                  }
                  answers
                />
              }}
           </div>
         )
       ->React.array}
    </Animation.Presence>
    <Button onClick={_ => setQuestions(Question.add(_, Open))}>
      <Text color=`white> {j|Dodaj pytanie otwarte|j} </Text>
    </Button>
    <Button onClick={_ => setQuestions(Question.add(_, Closed([||])))}>
      <Text color=`white> {j|Dodaj pytanie zamknięte|j} </Text>
    </Button>
    <Button onClick={_ => setQuestions(Question.add(_, Rate([||])))}>
      <Text color=`white> {j|Dodaj pytanie z oceną|j} </Text>
    </Button>
  </Layout>;
};